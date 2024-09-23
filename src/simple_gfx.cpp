#include <cassert>
#include <cmath>
#include <cstring>
#include <simple_gfx.hpp>
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

static GLFWwindow *window;
simple_gfx::KeyState input_state[349];
simple_gfx::Vector2<double> mouse_pos;
simple_gfx::Vector2<simple_gfx::KeyState> mouse_state;
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
