#ifndef XLIBWINDOW
#define XLIBWINDOW
#ifdef __linux__
#include "XlibWindow.h"
#include <iostream>
namespace FS {
XlibWindow::XlibWindow(const char *name, uint32_t width, uint32_t height) {
    mDisplay = XOpenDisplay(NULL);
    mScreen = DefaultScreen(mDisplay);
    XWindow rootWindow = XDefaultRootWindow(mDisplay);
    mWindowHandle = XCreateSimpleWindow(mDisplay, rootWindow, 0, 0, width, height, 0, 0, 0x000000);
    XMapWindow(mDisplay, mWindowHandle);
    mGc = DefaultGC(mDisplay, mScreen);
    input = {};
    renderState.width = width;
    renderState.height = height;

    int bufferSize = width * height * sizeof(uint32_t);
    if (renderState.screenBuffer)
        free(renderState.screenBuffer);
    renderState.screenBuffer = (uint32_t *)malloc(bufferSize);

    if (renderState.depthBuffer)
        free(renderState.depthBuffer);
    renderState.depthBuffer = (float *)malloc(width * height * sizeof(float));

    XSelectInput(mDisplay, mWindowHandle, KeyPressMask | KeyReleaseMask);

    XColor dummyColor;
    emptyPixmap = XCreatePixmap(mDisplay, mWindowHandle, 1, 1, 1);
    defaultCursor = XCreateFontCursor(mDisplay, XC_arrow);
    hiddenCursor = XCreatePixmapCursor(mDisplay,
                                       emptyPixmap,
                                       emptyPixmap,
                                       &dummyColor, &dummyColor, 0, 0);

    mBackImage = XCreateImage(mDisplay,
                              DefaultVisual(mDisplay, mScreen),
                              DefaultDepth(mDisplay, mScreen),
                              ZPixmap,
                              0,
                              NULL,
                              renderState.width,
                              renderState.height,
                              32,
                              renderState.width * 4);
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
    for (int y = 0; y < renderState.height; y++) {
        for (int x = 0; x < renderState.width; x++) {
            uint32_t index = ((renderState.width * y) + x);
            uint32_t pixel = (((uint32_t *)renderState.screenBuffer)[index]);
            XPutPixel(mBackImage, x, y, pixel);
        }
    }
    XPutImage(mDisplay, mWindowHandle, mGc, mBackImage, 0, 0, 0, 0, renderState.width, renderState.height);
}
void XlibWindow::processMessages() {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        input.buttons[i].changed = false;
    }
    if (!isOpen())
        return;
    while (XPending(mDisplay) > 0) {
        XEvent event;
        XNextEvent(mDisplay, &event);
        if (event.type == KeyPress || event.type == KeyRelease) {
            bool isDown = (event.type == KeyPress);
            KeySym keyCode = XLookupKeysym(&event.xkey, 0);
            switch (keyCode) {
#define process_message(b, kc)                                          \
    case kc: {                                                          \
        input.buttons[b].changed = (isDown != input.buttons[b].isDown); \
        input.buttons[b].isDown = isDown;                               \
    } break
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
                process_message(BUTTON_LEFT, XK_Left);
                process_message(BUTTON_RIGHT, XK_Right);
                process_message(BUTTON_UP, XK_Up);
                process_message(BUTTON_DOWN, XK_Down);
                process_message(BUTTON_ESC, XK_Escape);
                process_message(BUTTON_SHIFT, XK_Shift_L);
                process_message(BUTTON_SHIFT, XK_Shift_R);
                process_message(BUTTON_CTRL, XK_Control_L);
                process_message(BUTTON_CTRL, XK_Control_R);
                process_message(BUTTON_SPACE, XK_space);
            }
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
    XWarpPointer(mDisplay, None, mWindowHandle, 0, 0, 0, 0, x, y);
    XFlush(mDisplay);
}
Vector2 XlibWindow::getWindowPos() const {
    if (!isOpen())
        return { -1, -1 };
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
        return { (float)x, (float)y };
    }
    if (nitems != 4) {
        return { (float)x, (float)y };
    }
    long *extents = (long *)data;
    long left = 0, top = 0;
    left = extents[0];
    top = extents[2];
    x -= left;
    y -= top;
    XFree(data);
    return { (float)x, (float)(y) };
}
Vector2 XlibWindow::getCursorPos() const {
    if (!isOpen())
        return { -1, -1 };
    XWindow root, child;
    root = XDefaultRootWindow(mDisplay);
    int x, y;
    uint32_t mask;
    XQueryPointer(mDisplay, mWindowHandle, &root, &child, &x, &y, nullptr, nullptr, &mask);

    return { (float)x, (float)y };
}

void XlibWindow::removeConsole() const {
    std::fclose(stdout);
};

bool XlibWindow::isFocused() const {
    Window focusedWindow;
    int revertTo;
    XGetInputFocus(display,&focused,&revertTo);
    return (focusedWindow == mWindowHandle);
}
} // namespace FS

#endif
#endif
