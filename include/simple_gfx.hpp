#pragma once

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

void draw_rectangle(Vector2<double> pos, Vector2<double> size, Color color);

} // namespace simple_gfx
