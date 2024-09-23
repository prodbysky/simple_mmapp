#pragma once

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
} // namespace simple_gfx
