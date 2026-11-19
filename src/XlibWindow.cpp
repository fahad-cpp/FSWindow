#ifdef __linux__
#ifndef XLIBWINDOW
#define XLIBWINDOW
#include "XlibWindow.h"
#include <cstring>
#include <iostream>
namespace FS {
XlibWindow::XlibWindow(const char *name [[maybe_unused]], uint32_t width, uint32_t height) {
    mDisplay = XOpenDisplay(NULL);
    mScreen = DefaultScreen(mDisplay);
    XWindow rootWindow = XDefaultRootWindow(mDisplay);
    mWindowHandle = XCreateSimpleWindow(mDisplay, rootWindow, 0, 0, width, height, 0, 0, 0x000000);
    XMapWindow(mDisplay, mWindowHandle);
    mGc = DefaultGC(mDisplay, mScreen);
    input = {};
    renderState.width = width;
    renderState.height = height;

    uint32_t bufferSize = width * height * sizeof(uint32_t);
    if (renderState.screenBuffer)
        free(renderState.screenBuffer);
    renderState.screenBuffer = (uint32_t *)malloc(bufferSize);

    if (renderState.depthBuffer)
        free(renderState.depthBuffer);
    renderState.depthBuffer = (float *)malloc(width * height * sizeof(float));

    XSelectInput(mDisplay, mWindowHandle, KeyPressMask | KeyReleaseMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);

    XColor dummyColor;
    emptyPixmap = XCreatePixmap(mDisplay, mWindowHandle, 1, 1, 1);
    defaultCursor = XCreateFontCursor(mDisplay, XC_arrow);
    hiddenCursor = XCreatePixmapCursor(mDisplay,
                                       emptyPixmap,
                                       emptyPixmap,
                                       &dummyColor, &dummyColor, 0, 0);

    mBackImage = XCreateImage(mDisplay,
                              DefaultVisual(mDisplay, mScreen),
                              static_cast<uint32_t>(DefaultDepth(mDisplay, mScreen)),
                              ZPixmap,
                              0,
                              NULL,
                              renderState.width,
                              renderState.height,
                              32,
                              static_cast<int>(renderState.width * 4));
    mBackImage->data = (char *)malloc(width * height * sizeof(uint32_t));
    XFlush(mDisplay);
}
XlibWindow::~XlibWindow() {
    XDestroyImage(mBackImage);
    if (renderState.screenBuffer)
        free(renderState.screenBuffer);
    if (renderState.depthBuffer)
        free(renderState.depthBuffer);
    if (isOpen())
        XDestroyWindow(mDisplay, mWindowHandle);
    XFreeCursor(mDisplay, hiddenCursor);
    XFreeCursor(mDisplay, defaultCursor);
    XFreePixmap(mDisplay, emptyPixmap);
    XCloseDisplay(mDisplay);
}
void XlibWindow::swapBuffers() {
    if (!isOpen())
        return;
    const std::size_t bytesToCopy = static_cast<std::size_t>(mBackImage->bytes_per_line * mBackImage->height);
    std::memcpy(mBackImage->data, renderState.screenBuffer, bytesToCopy);
    XPutImage(mDisplay, mWindowHandle, mGc, mBackImage, 0, 0, 0, 0, renderState.width, renderState.height);
}
void handleButtonEvent(FS::ButtonState &buttonState, bool isDown) {
    buttonState.changed = (isDown != buttonState.isDown);
    buttonState.isDown = isDown;
}
void XlibWindow::processMessages() {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        input.buttons[i].changed = false;
    }
#define process_message(b, kc)                                          \
    case kc: {                                                          \
        input.buttons[b].changed = (isDown != input.buttons[b].isDown); \
        input.buttons[b].isDown = isDown;                               \
    } break
    input.mouse.diff = {};
    if (!isOpen())
        return;
    while (XPending(mDisplay) > 0) {
        XEvent event;
        XNextEvent(mDisplay, &event);
        if (event.type == KeyPress || event.type == KeyRelease) {
            bool isDown = (event.type == KeyPress);
            KeySym keyCode = XLookupKeysym(&event.xkey, 0);
            if (keyCode == XK_Shift_L || keyCode == XK_Shift_R) {
                handleButtonEvent(input.buttons[BUTTON_SHIFT], isDown);
            }
            if (keyCode == XK_Control_L || keyCode == XK_Control_R) {
                handleButtonEvent(input.buttons[BUTTON_CTRL], isDown);
            }
            if (keyCode == XK_Alt_L || keyCode == XK_Alt_R) {
                handleButtonEvent(input.buttons[BUTTON_ALT], isDown);
            }
            switch (keyCode) {
                // Action keys
                process_message(BUTTON_LSHIFT, XK_Shift_L);
                process_message(BUTTON_RSHIFT, XK_Shift_R);
                process_message(BUTTON_LCTRL, XK_Control_L);
                process_message(BUTTON_RCTRL, XK_Control_R);
                process_message(BUTTON_SPACE, XK_space);
                process_message(BUTTON_ESC, XK_Escape);
                process_message(BUTTON_LALT, XK_Alt_L);
                process_message(BUTTON_RALT, XK_Alt_R);
                process_message(BUTTON_TAB, XK_Tab);
                process_message(BUTTON_CAPSLOCK, XK_Caps_Lock);
                process_message(BUTTON_ENTER, XK_Return);
                process_message(BUTTON_BACKSPACE, XK_BackSpace);
                // Arrow
                process_message(BUTTON_UP, XK_Up);
                process_message(BUTTON_DOWN, XK_Down);
                process_message(BUTTON_LEFT, XK_Left);
                process_message(BUTTON_RIGHT, XK_Right);
                // Alphabets
                process_message(BUTTON_A, XK_a);
                process_message(BUTTON_A, XK_A);
                process_message(BUTTON_B, XK_b);
                process_message(BUTTON_B, XK_B);
                process_message(BUTTON_C, XK_c);
                process_message(BUTTON_C, XK_C);
                process_message(BUTTON_D, XK_d);
                process_message(BUTTON_D, XK_D);
                process_message(BUTTON_E, XK_e);
                process_message(BUTTON_E, XK_E);
                process_message(BUTTON_F, XK_f);
                process_message(BUTTON_F, XK_F);
                process_message(BUTTON_G, XK_g);
                process_message(BUTTON_G, XK_G);
                process_message(BUTTON_H, XK_h);
                process_message(BUTTON_H, XK_H);
                process_message(BUTTON_I, XK_i);
                process_message(BUTTON_I, XK_I);
                process_message(BUTTON_J, XK_j);
                process_message(BUTTON_J, XK_J);
                process_message(BUTTON_K, XK_k);
                process_message(BUTTON_K, XK_K);
                process_message(BUTTON_L, XK_l);
                process_message(BUTTON_L, XK_L);
                process_message(BUTTON_M, XK_m);
                process_message(BUTTON_M, XK_M);
                process_message(BUTTON_N, XK_n);
                process_message(BUTTON_N, XK_N);
                process_message(BUTTON_O, XK_o);
                process_message(BUTTON_O, XK_O);
                process_message(BUTTON_P, XK_p);
                process_message(BUTTON_P, XK_P);
                process_message(BUTTON_Q, XK_q);
                process_message(BUTTON_Q, XK_Q);
                process_message(BUTTON_R, XK_r);
                process_message(BUTTON_R, XK_R);
                process_message(BUTTON_S, XK_s);
                process_message(BUTTON_S, XK_S);
                process_message(BUTTON_T, XK_t);
                process_message(BUTTON_T, XK_T);
                process_message(BUTTON_U, XK_u);
                process_message(BUTTON_U, XK_U);
                process_message(BUTTON_V, XK_v);
                process_message(BUTTON_V, XK_V);
                process_message(BUTTON_W, XK_w);
                process_message(BUTTON_W, XK_W);
                process_message(BUTTON_X, XK_x);
                process_message(BUTTON_X, XK_X);
                process_message(BUTTON_Y, XK_y);
                process_message(BUTTON_Y, XK_Y);
                process_message(BUTTON_Z, XK_z);
                process_message(BUTTON_Z, XK_Z);
                // Numbers
                process_message(BUTTON_NUMLOCK, XK_Num_Lock);
                process_message(BUTTON_0, XK_0);
                process_message(BUTTON_1, XK_1);
                process_message(BUTTON_2, XK_2);
                process_message(BUTTON_3, XK_3);
                process_message(BUTTON_4, XK_4);
                process_message(BUTTON_5, XK_5);
                process_message(BUTTON_6, XK_6);
                process_message(BUTTON_7, XK_7);
                process_message(BUTTON_8, XK_8);
                process_message(BUTTON_9, XK_9);
                process_message(BUTTON_NUMPAD_0, XK_KP_0);
                process_message(BUTTON_NUMPAD_1, XK_KP_1);
                process_message(BUTTON_NUMPAD_2, XK_KP_2);
                process_message(BUTTON_NUMPAD_3, XK_KP_3);
                process_message(BUTTON_NUMPAD_4, XK_KP_4);
                process_message(BUTTON_NUMPAD_5, XK_KP_5);
                process_message(BUTTON_NUMPAD_6, XK_KP_6);
                process_message(BUTTON_NUMPAD_7, XK_KP_7);
                process_message(BUTTON_NUMPAD_8, XK_KP_8);
                process_message(BUTTON_NUMPAD_9, XK_KP_9);
                // function
                process_message(BUTTON_F1, XK_F1);
                process_message(BUTTON_F2, XK_F2);
                process_message(BUTTON_F3, XK_F3);
                process_message(BUTTON_F4, XK_F4);
                process_message(BUTTON_F5, XK_F5);
                process_message(BUTTON_F6, XK_F6);
                process_message(BUTTON_F7, XK_F7);
                process_message(BUTTON_F8, XK_F8);
                process_message(BUTTON_F9, XK_F9);
                process_message(BUTTON_F10, XK_F10);
                process_message(BUTTON_F11, XK_F11);
                process_message(BUTTON_F12, XK_F12);
            }
        } else if (event.type == ButtonPress || event.type == ButtonRelease) {
            bool isDown = event.type == ButtonPress;
            switch (event.xbutton.button) {
                process_message(MOUSE_BUTTON_LEFT, Button1);
                process_message(MOUSE_BUTTON_MIDDLE, Button2);
                process_message(MOUSE_BUTTON_RIGHT, Button3);
                process_message(MOUSE_BUTTON_EXTRA1, Button4);
                process_message(MOUSE_BUTTON_EXTRA2, Button5);
            }
        } else if (event.type == ConfigureNotify) {
            XConfigureEvent *configureEvent = &event.xconfigure;
            renderState.width = static_cast<uint32_t>(configureEvent->width);
            renderState.height = static_cast<uint32_t>(configureEvent->height);

            uint32_t resolution = renderState.width * renderState.height;
            if (renderState.screenBuffer)
                free(renderState.screenBuffer);
            renderState.screenBuffer = (uint32_t *)malloc(resolution * sizeof(uint32_t));

            if (renderState.depthBuffer)
                free(renderState.depthBuffer);
            renderState.depthBuffer = (float *)malloc(resolution * sizeof(float));

            XDestroyImage(mBackImage);
            mBackImage = XCreateImage(mDisplay,
                                      DefaultVisual(mDisplay, mScreen),
                                      static_cast<uint32_t> DefaultDepth(mDisplay, mScreen),
                                      ZPixmap,
                                      0,
                                      NULL,
                                      renderState.width,
                                      renderState.height,
                                      32,
                                      static_cast<int>(renderState.width * 4));
            mBackImage->data = (char *)malloc(resolution * sizeof(uint32_t));
            XFlush(mDisplay);
        } else if (event.type == MotionNotify) {
            FS::Vector2 newPos = {static_cast<float>(event.xmotion.x), static_cast<float>(event.xmotion.y)};
            input.mouse.diff = newPos - input.mouse.pos;
            input.mouse.pos = newPos;
        }
    }
};
void XlibWindow::addConsole() const {
    std::freopen("/dev/tty", "w", stdout);
};

void XlibWindow::showCursor(bool show) {
    if (show) {
        XDefineCursor(mDisplay, mWindowHandle, defaultCursor);
    } else {
        XDefineCursor(mDisplay, mWindowHandle, hiddenCursor);
    }
}
void XlibWindow::setWindowPos(int x, int y) {
    if (!isOpen())
        return;
    XSync(mDisplay, False);
    XMoveWindow(mDisplay, mWindowHandle, x, y);
    XFlush(mDisplay);
}
void XlibWindow::setCursorPos(uint32_t x, uint32_t y) {
    XWindow rootWindow = XDefaultRootWindow(mDisplay);
    XWarpPointer(mDisplay, None, rootWindow, 0, 0, 0, 0, int(x), int(y));
    XFlush(mDisplay);
}

void XlibWindow::focus() const {
    XSetInputFocus(mDisplay, mWindowHandle, RevertToNone, CurrentTime);
}

Vector2 XlibWindow::getWindowPos(bool excludeFrames) const {
    if (!isOpen())
        return {-1, -1};
    XWindow rootWindow = XRootWindow(mDisplay, mScreen);
    XWindow child;
    int x, y;
    XTranslateCoordinates(mDisplay, mWindowHandle, rootWindow, 0, 0, &x, &y, &child);

    Atom prop = XInternAtom(mDisplay, "_NET_FRAME_EXTENTS", False);
    Atom actualType;
    int actualFormart;
    uint64_t nitems, bytesAfter;
    uint8_t *data = NULL;
    int status = XGetWindowProperty(mDisplay, mWindowHandle, prop, 0, 4, False, XA_CARDINAL, &actualType, &actualFormart, &nitems, &bytesAfter, &data);

    if ((status != Success)) {
        std::cerr << "failed to get window property\n";
        std::cerr << "status:" << status << "\n";
        return {static_cast<float>(x), static_cast<float>(y)};
    }
    if (nitems != 4) {
        return {static_cast<float>(x), static_cast<float>(y)};
    }
    long *extents = (long *)data;
    long left = 0, top = 0;
    left = extents[0];
    top = extents[2];
    if (!excludeFrames) {
        x -= static_cast<int>(left);
        y -= static_cast<int>(top);
    }
    XFree(data);
    return {static_cast<float>(x), static_cast<float>(y)};
}
Vector2 XlibWindow::getCursorPos(bool clientSpace) const {
    if (!isOpen())
        return {-1, -1};
    XWindow root, child;
    root = XDefaultRootWindow(mDisplay);
    int x, y;
    int wx, wy;
    uint32_t mask;
    XQueryPointer(mDisplay, mWindowHandle, &root, &child, &x, &y, &wx, &wy, &mask);

    if (clientSpace) {
        return {static_cast<float>(wx), static_cast<float>(wy)};
    }
    return {static_cast<float>(x), static_cast<float>(y)};
}

void XlibWindow::removeConsole() const {
    std::fclose(stdout);
};

bool XlibWindow::isFocused() const {
    XWindow focusedWindow;
    int revertTo;
    XGetInputFocus(mDisplay, &focusedWindow, &revertTo);
    return (focusedWindow == mWindowHandle);
}
} // namespace FS

#endif
#endif
