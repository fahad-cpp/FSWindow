#ifndef FSINPUT_H
#define FSINPUT_H
#include <cstdint>
#include <string_view>
#include "FSVector2.h"

namespace FS {
// TODO(fahad-cpp) : x11 : Numpad , left and right keys , ALT,capslock,enter,backspace,TAB,Function,
// TODO(fahad-cpp) : win32 : fix left and right buttons, handle extra mouse buttons 
// TODO(fahad-cpp) : differentiate between capital and small letters
enum Button : uint8_t {
    // Action
    BUTTON_SHIFT, // LSHIFT OR RSHIFT
    BUTTON_LSHIFT,
    BUTTON_RSHIFT,
    BUTTON_CTRL, // LCTRL OR RCTRL
    BUTTON_LCTRL,
    BUTTON_RCTRL,
    BUTTON_SPACE,
    BUTTON_ESC,
    BUTTON_ALT,
    BUTTON_LALT,
    BUTTON_RALT,
    BUTTON_TAB,
    BUTTON_CAPSLOCK,
    BUTTON_ENTER,
    BUTTON_BACKSPACE,
    // Arrow
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_RIGHT,
    BUTTON_LEFT,
    // Mouse
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_EXTRA1,
    MOUSE_BUTTON_EXTRA2,
    MOUSE_BUTTON_EXTRA3,
    MOUSE_BUTTON_EXTRA4,
    MOUSE_BUTTON_EXTRA5,
    // Numbers
    BUTTON_NUMLOCK,
    BUTTON_0,
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,
    BUTTON_4,
    BUTTON_5,
    BUTTON_6,
    BUTTON_7,
    BUTTON_8,
    BUTTON_9,
    BUTTON_NUMPAD_0,
    BUTTON_NUMPAD_1,
    BUTTON_NUMPAD_2,
    BUTTON_NUMPAD_3,
    BUTTON_NUMPAD_4,
    BUTTON_NUMPAD_5,
    BUTTON_NUMPAD_6,
    BUTTON_NUMPAD_7,
    BUTTON_NUMPAD_8,
    BUTTON_NUMPAD_9,
    // Alphabets
    BUTTON_A,
    BUTTON_B,
    BUTTON_C,
    BUTTON_D,
    BUTTON_E,
    BUTTON_F,
    BUTTON_G,
    BUTTON_H,
    BUTTON_I,
    BUTTON_J,
    BUTTON_K,
    BUTTON_L,
    BUTTON_M,
    BUTTON_N,
    BUTTON_O,
    BUTTON_P,
    BUTTON_Q,
    BUTTON_R,
    BUTTON_S,
    BUTTON_T,
    BUTTON_U,
    BUTTON_V,
    BUTTON_W,
    BUTTON_X,
    BUTTON_Y,
    BUTTON_Z,
    // Function
    BUTTON_F1,
    BUTTON_F2,
    BUTTON_F3,
    BUTTON_F4,
    BUTTON_F5,
    BUTTON_F6,
    BUTTON_F7,
    BUTTON_F8,
    BUTTON_F9,
    BUTTON_F10,
    BUTTON_F11,
    BUTTON_F12,

    BUTTON_COUNT
};
const std::string_view buttonName[BUTTON_COUNT] = {
    // Action
    "BUTTON_SHIFT", // LSHIFT OR RSHIFT
    "BUTTON_LSHIFT",
    "BUTTON_RSHIFT",
    "BUTTON_CTRL", // LCTRL OR RCTRL
    "BUTTON_LCTRL",
    "BUTTON_RCTRL",
    "BUTTON_SPACE",
    "BUTTON_ESC",
    "BUTTON_ALT",
    "BUTTON_LALT",
    "BUTTON_RALT",
    "BUTTON_TAB",
    "BUTTON_CAPSLOCK",
    "BUTTON_ENTER",
    "BUTTON_BACKSPACE",
    // Arrow
    "BUTTON_UP",
    "BUTTON_DOWN",
    "BUTTON_RIGHT",
    "BUTTON_LEFT",
    // Mouse
    "MOUSE_BUTTON_LEFT",
    "MOUSE_BUTTON_RIGHT",
    "MOUSE_BUTTON_MIDDLE",
    "MOUSE_BUTTON_EXTRA1",
    "MOUSE_BUTTON_EXTRA2",
    "MOUSE_BUTTON_EXTRA3",
    "MOUSE_BUTTON_EXTRA4",
    "MOUSE_BUTTON_EXTRA5",
    // Numbers
    "BUTTON_NUMLOCK",
    "BUTTON_0",
    "BUTTON_1",
    "BUTTON_2",
    "BUTTON_3",
    "BUTTON_4",
    "BUTTON_5",
    "BUTTON_6",
    "BUTTON_7",
    "BUTTON_8",
    "BUTTON_9",
    "BUTTON_NUMPAD_0",
    "BUTTON_NUMPAD_1",
    "BUTTON_NUMPAD_2",
    "BUTTON_NUMPAD_3",
    "BUTTON_NUMPAD_4",
    "BUTTON_NUMPAD_5",
    "BUTTON_NUMPAD_6",
    "BUTTON_NUMPAD_7",
    "BUTTON_NUMPAD_8",
    "BUTTON_NUMPAD_9",
    // Alphabets
    "BUTTON_A",
    "BUTTON_B",
    "BUTTON_C",
    "BUTTON_D",
    "BUTTON_E",
    "BUTTON_F",
    "BUTTON_G",
    "BUTTON_H",
    "BUTTON_I",
    "BUTTON_J",
    "BUTTON_K",
    "BUTTON_L",
    "BUTTON_M",
    "BUTTON_N",
    "BUTTON_O",
    "BUTTON_P",
    "BUTTON_Q",
    "BUTTON_R",
    "BUTTON_S",
    "BUTTON_T",
    "BUTTON_U",
    "BUTTON_V",
    "BUTTON_W",
    "BUTTON_X",
    "BUTTON_Y",
    "BUTTON_Z",
    // Function
    "BUTTON_F1",
    "BUTTON_F2",
    "BUTTON_F3",
    "BUTTON_F4",
    "BUTTON_F5",
    "BUTTON_F6",
    "BUTTON_F7",
    "BUTTON_F8",
    "BUTTON_F9",
    "BUTTON_F10",
    "BUTTON_F11",
    "BUTTON_F12",
};
struct ButtonState {
    bool isDown;
    bool changed;
};
struct MouseState {
    FS::Vector2 pos;
    FS::Vector2 diff;
};
// TODO(fahad-cpp) : handle mousediff and mousepos for x11
// TODO(fahad-cpp) : replace the array with bitmasks of `isDown` and `changed`
struct Input {
    ButtonState buttons[BUTTON_COUNT];
    MouseState mouse;
    inline bool isDown(const Button button) const {
        return buttons[button].isDown;
    }
    inline bool pressed(const Button button) const {
        return (buttons[button].isDown && buttons[button].changed);
    }
    inline bool released(const Button button) const {
        return ((!buttons[button].isDown) && buttons[button].changed);
    }
};
} // namespace FS
#endif
