#pragma once

#include "simple_gfx_vector.hpp"
namespace simple_gfx {

    void create_window(int width, int height, const char* title);
    bool window_should_close();
    void window_clear(Color color);
    void begin_drawing();
    void end_drawing();
    void destroy_window();
    double get_frametime();

    void draw_rectangle(Vector2<float> pos, Vector2<float> size, Color color);

} // namespace simple_gfx
