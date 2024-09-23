#pragma once
#include <type_traits>
namespace simple_gfx {
template <typename T> union Vector2 {
  struct {
    T x, y;
  };
  struct {
    T u, v;
  };
  struct {
    T w, h;
  };
  struct {
    T first, second;
  };

  static Vector2<T> Zero() {
    static_assert(std::is_integral<T>::value,
                  "Tried to make a zero vector of non-number types");
    return {0, 0};
  }
  static Vector2<T> One() {
    static_assert(std::is_integral<T>::value,
                  "Tried to make a one vector of non-number types");
    return {1, 1};
  }
};
} // namespace simple_gfx
