#include "simple_gfx_input.hpp"

#include "simple_gfx_vector.hpp"

#include <cassert>

extern simple_gfx::KeyState input_state[349];
extern simple_gfx::Vector2<double> mouse_pos;
extern simple_gfx::Vector2<simple_gfx::KeyState> mouse_state;

namespace simple_gfx {
    // Shout out to stackoverflow:
    // https://stackoverflow.com/questions/11421432/how-can-i-output-the-value-of-an-enum-class-in-c11
    template <typename E>
    constexpr typename std::underlying_type<E>::type
    to_underlying(E e) noexcept {
        return static_cast<typename std::underlying_type<E>::type>(e);
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
            assert(false &&
                   "Not supported mouse key passed in is_mouse_key_down");
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
            assert(false &&
                   "Not supported mouse key passed in is_mouse_key_pressed");
        }
        return false;
    }

    Vector2<double> get_mouse_pos() { return mouse_pos; }
} // namespace simple_gfx
