#include "../include/simple_gfx.hpp"

int main() {
  simple_gfx::create_window(1280, 720, "Hello!");
  while (!simple_gfx::window_should_close()) {
    simple_gfx::begin_drawing();
    simple_gfx::window_clear({.color = 0x181818ff});
    simple_gfx::draw_rectangle({250, 250}, {64, 64}, {.color = 0x00112233});
    simple_gfx::end_drawing();
  }
  simple_gfx::destroy_window();
}
