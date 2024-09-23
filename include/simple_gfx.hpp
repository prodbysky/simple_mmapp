#pragma once

#include "simple_gfx_input.hpp"
#include "simple_gfx_vector.hpp"

#include <cstdint>
namespace simple_gfx {
union Color {
  uint32_t color;
  struct {
    uint8_t a;
    uint8_t b;
    uint8_t g;
    uint8_t r;
  };
};

void create_window(int width, int height, const char *title);
bool window_should_close();
void window_clear(Color color);
void begin_drawing();
void end_drawing();
void destroy_window();

// Pressed or held down
bool is_key_down(Key key);
bool is_mouse_key_down(Key key);
// Just pressed
bool is_key_pressed(Key key);
bool is_mouse_key_pressed(Key key);
Vector2<double> get_mouse_pos();

} // namespace simple_gfx
