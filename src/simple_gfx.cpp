#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <simple_gfx.hpp>
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

static const char *vert_shader_source = R"(
uniform vec2 screenSize;
uniform vec4 color;
uniform vec2 transform_pos;
uniform vec2 transform_size;

out vec4 fragColor;

void main()
{
  vec2 vertices[6] =
  {
    transform_pos,                                        // Top Left
    vec2(transform_pos + vec2(0.0, transform_size.y)),    // Bottom Left
    vec2(transform_pos + vec2(transform_size.x, 0.0)),    // Top Right
    vec2(transform_pos + vec2(transform_size.x, 0.0)),    // Top Right
    vec2(transform_pos + vec2(0.0, transform_size.y)),    // Bottom Left
    transform_pos + transform_size                        // Bottom Right
  };

  // Normalize Position
  {
    vec2 vertexPos = vertices[gl_VertexID];
    gl_Position = vec4(((vertexPos / screenSize) * 2) - 1, 1.0, 1.0);
  }
  fragColor = color;
}
)";

static const char *frag_shader_source = R"(
in vec4 fragColor;
layout (location = 0) out vec4 outColor;

void main()
{
    if (fragColor.a == 0.0) {
    discard;
    }
    outColor = fragColor;
}
)";
static GLFWwindow *window;
simple_gfx::KeyState input_state[349];
simple_gfx::Vector2<double> mouse_pos;
simple_gfx::Vector2<simple_gfx::KeyState> mouse_state;
static uint32_t quad_shader;
namespace simple_gfx {

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods);
static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos);

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods);

void create_window(int width, int height, const char *title) {
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
  mouse_state.first = KeyState::Released;
  mouse_state.second = KeyState::Released;

  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  uint32_t vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vert_shader_source, nullptr);
  glCompileShader(vert_shader);
  uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag_shader_source, nullptr);
  glCompileShader(frag_shader);
  quad_shader = glCreateProgram();
  glAttachShader(quad_shader, vert_shader);
  glAttachShader(quad_shader, frag_shader);
  glLinkProgram(quad_shader);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
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

static void key_callback(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
  if (action == GLFW_PRESS) {
    input_state[key] = KeyState::Pressed;
  } else if (action == GLFW_REPEAT) {
    input_state[key] = KeyState::Held;
  } else if (action == GLFW_RELEASE) {
    input_state[key] = KeyState::Released;
  }
}
static void cursor_position_callback(GLFWwindow *window, double xpos,
                                     double ypos) {
  mouse_pos.x = xpos;
  mouse_pos.y = ypos;
}

static void mouse_button_callback(GLFWwindow *window, int button, int action,
                                  int mods) {
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

} // namespace simple_gfx
