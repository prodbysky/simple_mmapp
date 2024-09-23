#include <simple_gfx.hpp>
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

static GLFWwindow *window;

namespace simple_gfx {
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
} // namespace simple_gfx
