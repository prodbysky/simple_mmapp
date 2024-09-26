#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <simple_gfx.hpp>
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <simple_gfx_input.hpp>
#include <simple_gfx_vector.hpp>

static const char* vert_shader_source = R"(
#version 330 core
uniform vec4 color; 
uniform vec2 transform_pos; 
uniform vec2 transform_size; 
uniform mat4 proj;

out vec4 fragColor;

void main()
{

  vec2 vertices[6];
  vertices[0] = transform_pos;                                       // Top Left
  vertices[1] = transform_pos + vec2(0.0, transform_size.y);         // Bottom Left
  vertices[2] = transform_pos + vec2(transform_size.x, 0.0);         // Top Right
  vertices[3] = transform_pos + vec2(transform_size.x, 0.0);         // Top Right
  vertices[4] = transform_pos + vec2(0.0, transform_size.y);         // Bottom Left
  vertices[5] = transform_pos + transform_size;                      // Bottom Right

  // Normalize Position
  {
    vec2 vertexPos = vertices[gl_VertexID];
    gl_Position = vec4(vertexPos, 1, 1)* proj;
    gl_Position = proj * vec4(vertexPos, 1, 1);
  }
  fragColor = color;
}
)";

static const char* frag_shader_source = R"(
#version 330 core
in vec4 fragColor;
out vec4 outColor;

void main() {

    if (fragColor.a == 0.0) {
    discard;
    }
    outColor = fragColor;
}
)";

static GLFWwindow* window;
simple_gfx::KeyState input_state[349];
simple_gfx::Vector2<double> mouse_pos;
simple_gfx::Vector2<simple_gfx::KeyState> mouse_state;
static uint32_t quad_shader;
static glm::mat4 proj;
static simple_gfx::Vector2<float> window_size;

namespace simple_gfx {

    static void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos,
                                         double ypos);

    static void mouse_button_callback(GLFWwindow* window, int button,
                                      int action, int mods);

    static void framebuffer_size_callback(GLFWwindow* window, int width,
                                          int height);
    static void compile_shader() {
        uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert_shader, 1, &vert_shader_source, nullptr);
        glCompileShader(vert_shader);
        char buf[512];
        int success;
        glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vert_shader, 512, NULL, buf);
            std::cout << "Failed to compile vertex shader: " << buf << '\n';
        }
        uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag_shader, 1, &frag_shader_source, nullptr);
        glCompileShader(frag_shader);
        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(frag_shader, 512, NULL, buf);
            std::cout << "Failed to compile fragment shader: " << buf << '\n';
        }
        quad_shader = glCreateProgram();
        glAttachShader(quad_shader, vert_shader);
        glAttachShader(quad_shader, frag_shader);
        glLinkProgram(quad_shader);

        glGetShaderiv(frag_shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(quad_shader, 512, NULL, buf);
            std::cout << "Failed to link shader: " << buf << '\n';
        }

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);
    }
    void create_window(int width, int height, const char* title) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        if (!glfwInit())
            return;

        window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            destroy_window();
            return;
        }

        glfwMakeContextCurrent(window);

        gladLoadGL();
        memset(input_state, 0, sizeof(input_state));
        mouse_state.first  = KeyState::Released;
        mouse_state.second = KeyState::Released;

        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        compile_shader();

        proj = glm::ortho(0.0f, (float) width, (float) height, 0.0f, -10.0f,
                          10.0f);
    }
    bool window_should_close() { return glfwWindowShouldClose(window); }
    void destroy_window() { glfwTerminate(); }

    void window_clear(Color color) {
        glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0,
                     color.a / 255.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void begin_drawing() {}

    void end_drawing() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void set_shader_uniform_vec2(const char* name, Vector2<float> data) {
        glUseProgram(quad_shader);
        const int32_t location = glGetUniformLocation(quad_shader, name);
        if (location == -1) {
            std::cerr << "Tried to get location of non-existent vec2 uniform: "
                      << name << '\n';
            return;
        }
        glUniform2fv(location, 1, (float[]){data.x, data.y});
    }

    void set_shader_uniform_vec4(const char* name, Vector4<float> data) {
        glUseProgram(quad_shader);
        const int32_t location = glGetUniformLocation(quad_shader, name);
        if (location == -1) {
            std::cerr << "Tried to get location of non-existent vec4 uniform: "
                      << name << '\n';
            return;
        }
        glUniform4fv(location, 1, (float[]){data.r, data.g, data.b, data.a});
    }

    void set_shader_uniform_mat4(const char* name, glm::mat4 data) {
        glUseProgram(quad_shader);
        const uint32_t location = glGetUniformLocation(quad_shader, name);
        if (location == -1) {
            std::cerr << "Tried to get location of non-existent vec4 uniform: "
                      << name << '\n';
            return;
        }
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
    }

    void draw_rectangle(Vector2<float> pos, Vector2<float> size, Color color) {
        glUseProgram(quad_shader);
        set_shader_uniform_vec4("color", color.Normalize());
        set_shader_uniform_vec2("transform_size", size);
        set_shader_uniform_vec2("transform_pos", pos);
        set_shader_uniform_mat4("proj", proj);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 1);
    }

    static void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods) {
        if (action == GLFW_PRESS) {
            input_state[key] = KeyState::Pressed;
        } else if (action == GLFW_REPEAT) {
            input_state[key] = KeyState::Held;
        } else if (action == GLFW_RELEASE) {
            input_state[key] = KeyState::Released;
        }
    }
    static void cursor_position_callback(GLFWwindow* window, double xpos,
                                         double ypos) {
        mouse_pos.x = xpos;
        mouse_pos.y = ypos;
    }

    static void mouse_button_callback(GLFWwindow* window, int button,
                                      int action, int mods) {
        assert(button < 2);

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                mouse_state.first = KeyState::Pressed;
            } else if (action == GLFW_REPEAT) {
                mouse_state.first = KeyState::Held;
            } else if (action == GLFW_RELEASE) {
                mouse_state.first = KeyState::Held;
            }
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            if (action == GLFW_PRESS) {
                mouse_state.second = KeyState::Pressed;
            } else if (action == GLFW_REPEAT) {
                mouse_state.second = KeyState::Held;
            } else if (action == GLFW_RELEASE) {
                mouse_state.second = KeyState::Held;
            }
        }
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width,
                                          int height) {
        proj = glm::ortho(0.0f, (float) width, (float) height, 0.0f, -10.0f,
                          10.0f);
        window_size.first  = width;
        window_size.second = height;
        glViewport(0, 0, width, height);
    }

} // namespace simple_gfx
