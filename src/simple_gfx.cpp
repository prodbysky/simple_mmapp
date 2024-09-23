#include <cassert>
#include <cmath>
#include <cstring>
#include <simple_gfx.hpp>
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

static GLFWwindow *window;
static simple_gfx::KeyState input_state[349];
static simple_gfx::Vector2<double> mouse_pos;
static simple_gfx::Vector2<simple_gfx::KeyState> mouse_state;
namespace simple_gfx {

template <typename E>
static constexpr typename std::underlying_type<E>::type
to_underlying(E e) noexcept {
  return static_cast<typename std::underlying_type<E>::type>(e);
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

bool is_key_down(Key key) {
  if (to_underlying(key) > 348) {
    assert(false && "Not supported keyboard key passed in is_key_down");
  }
  return input_state[to_underlying(key)] == KeyState::Held ||
         input_state[to_underlying(key)] == KeyState::Pressed;
}

bool is_mouse_key_down(Key key) {
  if (key == Key::MouseLeft) {
    return mouse_state.first == KeyState::Held ||
           mouse_state.first == KeyState::Pressed;
  } else if (key == Key::MouseRight) {
    return mouse_state.second == KeyState::Held ||
           mouse_state.second == KeyState::Pressed;
  } else {
    assert(false && "Not supported mouse key passed in is_mouse_key_down");
  }
}

bool is_key_pressed(Key key) {

  if (input_state[to_underlying(key)] == KeyState::Pressed) {
    input_state[to_underlying(key)] = KeyState::Held;
    return true;
  }

  return false;
}
bool is_mouse_key_pressed(Key key) {
  if (key == Key::MouseLeft) {
    if (mouse_state.first == KeyState::Pressed) {
      mouse_state.first = KeyState::Held;
      return true;
    }
  } else if (key == Key::MouseRight) {
    if (mouse_state.second == KeyState::Pressed) {
      mouse_state.second = KeyState::Held;
      return true;
    }
  } else {
    assert(false && "Not supported mouse key passed in is_mouse_key_pressed");
  }
  return false;
}

Vector2<double> get_mouse_pos() { return mouse_pos; }
} // namespace simple_gfx
