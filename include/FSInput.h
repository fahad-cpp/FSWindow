#ifndef FSINPUT_H
#define FSINPUT_H
namespace FS {
// TODO(fahad-cpp) : Add NUMPAD and Numbers
// TODO(fahad-cpp) : replace CTRL and SHIFT with LCTRL/RCTRL and LSHIFT/RSHIFT
// TODO(fahad-cpp) : differentiate between capital and small letters
enum Buttons {
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
struct Input {
    ButtonState buttons[BUTTON_COUNT];
};
} // namespace FS
// TODO(fahad-cpp) : why did i hardcode this again?
#define isDown(x) input.buttons[x].isDown
#endif
