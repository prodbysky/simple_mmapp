#include "../include/simple_gfx.hpp"
#include <iostream>

int main() {
  simple_gfx::create_window(1280, 720, "Hello!");
  while (!simple_gfx::window_should_close()) {
    simple_gfx::begin_drawing();
    simple_gfx::window_clear({.color = 0x181818ff});
    simple_gfx::end_drawing();
    if (simple_gfx::is_key_pressed(simple_gfx::Key::A)) {
      std::cout << simple_gfx::get_mouse_pos().x << " "
                << simple_gfx::get_mouse_pos().y << '\n';
    }
  }
  simple_gfx::destroy_window();
}
