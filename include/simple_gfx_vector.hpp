#pragma once
#include <cstdint>
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

    template <typename T> union Vector4 {
        struct {
            T x, y, z, w;
        };
        struct {
            T a, b, g, r;
        };
        struct {
            T first, second, third, fourth;
        };
        uint32_t color;

        static Vector4<T> Zero() {
            static_assert(std::is_integral<T>::value,
                          "Tried to make a zero vector of non-number types");
            return {0, 0, 0, 0};
        }
        static Vector4<T> One() {
            static_assert(std::is_integral<T>::value,
                          "Tried to make a one vector of non-number types");
            return {1, 1, 1, 1};
        }

        Vector4<float> Normalize() {
            return {
                .a = a / 255.f,
                .b = b / 255.f,
                .g = g / 255.f,
                .r = r / 255.f,
            };
        }
    };

    using Color = Vector4<uint8_t>;

} // namespace simple_gfx
