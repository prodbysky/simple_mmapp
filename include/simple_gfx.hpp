#pragma once

#include <cstdint>
namespace simple_gfx {
enum class Key : uint16_t {
  Space = 32,
  Apostrophe = 39,
  Comma = 44,
  Minus = 45,
  Period = 46,
  Slash = 47,
  Zero = 48,
  One = 49,
  Two = 50,
  Three = 51,
  Four = 52,
  Five = 53,
  Six = 54,
  Seven = 55,
  Eight = 56,
  Nine = 57,
  Semicolon = 59,
  Equal = 61,
  A = 65,
  B = 66,
  C = 67,
  D = 68,
  E = 69,
  F = 70,
  G = 71,
  H = 72,
  I = 73,
  J = 74,
  K = 75,
  L = 76,
  M = 77,
  N = 78,
  O = 79,
  P = 80,
  Q = 81,
  R = 82,
  S = 83,
  T = 84,
  U = 85,
  V = 86,
  W = 87,
  X = 88,
  Y = 89,
  Z = 90,
  LeftBracket = 91,
  Backslash = 92,
  RightBracket = 93,
  GraveAccent = 96,
  World1 = 161,
  World2 = 162,
  Escape = 256,
  Enter = 257,
  Tab = 258,
  Backspace = 259,
  Insert = 260,
  Delete = 261,
  Right = 262,
  Left = 263,
  Down = 264,
  Up = 265,
  PageUp = 266,
  PageDown = 267,
  Home = 268,
  End = 269,
  CapsLock = 280,
  ScrollLock = 281,
  NumLock = 282,
  PrintScreen = 283,
  Pause = 284,
  F1 = 290,
  F2 = 291,
  F3 = 292,
  F4 = 293,
  F5 = 294,
  F6 = 295,
  F7 = 296,
  F8 = 297,
  F9 = 298,
  F10 = 299,
  F11 = 300,
  F12 = 301,
  F13 = 302,
  F14 = 303,
  F15 = 304,
  F16 = 305,
  F17 = 306,
  F18 = 307,
  F19 = 308,
  F20 = 309,
  F21 = 310,
  F22 = 311,
  F23 = 312,
  F24 = 313,
  F25 = 314,
  KeyPad0 = 320,
  KeyPad1 = 321,
  KeyPad2 = 322,
  KeyPad3 = 323,
  KeyPad4 = 324,
  KeyPad5 = 325,
  KeyPad6 = 326,
  KeyPad7 = 327,
  KeyPad8 = 328,
  KeyPad9 = 329,
  KeyPadDecimal = 330,
  KeyPadDivide = 331,
  KeyPadMultiply = 332,
  KeyPadSubtract = 333,
  KeyPadAdd = 334,
  KeyPadEnter = 335,
  KeyPadEqual = 336,
  LeftShift = 340,
  LeftControl = 341,
  LeftAlt = 342,
  LeftSuper = 343,
  RightShift = 344,
  RightControl = 345,
  RightAlt = 346,
  RightSuper = 347,
  Menu = 348,
  MouseLeft = 0,
  MouseRight = 1,
};

enum class KeyState : uint8_t {
  Released = 0,
  Pressed = 1,
  Held = 2,
};

union Color {
  uint32_t color;
  struct {
    uint8_t a;
    uint8_t b;
    uint8_t g;
    uint8_t r;
  };
};

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
