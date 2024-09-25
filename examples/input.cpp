#include "../include/simple_gfx.hpp"
#include "../include/simple_gfx_input.hpp"
#include <iostream>

int main() {
  simple_gfx::create_window(1280, 720, "Hello!");
  int i = 0;
  while (!simple_gfx::window_should_close()) {
    simple_gfx::begin_drawing();
    simple_gfx::window_clear({.color = 0x181818ff});
    simple_gfx::draw_rectangle({(float)i, 0}, {100, 100},
                               simple_gfx::Color{0xffaaccff});
    simple_gfx::end_drawing();
    if (simple_gfx::is_key_pressed(simple_gfx::Key::A)) {
      std::cout << simple_gfx::get_mouse_pos().x << " "
                << simple_gfx::get_mouse_pos().y << '\n';
    }
    i++;
  }
  simple_gfx::destroy_window();
}
