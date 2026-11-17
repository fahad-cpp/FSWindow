#ifndef FSINPUT_H
#define FSINPUT_H
#include <cstdint>
namespace FS {
// TODO(fahad-cpp) : Add NUMPAD
// TODO(fahad-cpp) : replace CTRL and SHIFT with LCTRL/RCTRL and LSHIFT/RSHIFT
// TODO(fahad-cpp) : differentiate between capital and small letters
enum Button : uint8_t{
    BUTTON_SHIFT,
    BUTTON_CTRL,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_RIGHT,
    BUTTON_LEFT,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    BUTTON_SPACE,
    BUTTON_ESC,
    //numbers
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
    // alphabets
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
    BUTTON_COUNT
};

struct ButtonState {
    bool isDown;
    bool changed;
};
// TODO(fahad-cpp) : Add mousediff and mousepos directly here and update in processMessages()
// TODO(fahad-cpp) : replace the array with bitset of `isDown` and `changed`
struct Input {
    ButtonState buttons[BUTTON_COUNT];
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
