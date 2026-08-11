#ifdef __linux__
#ifndef FSLINUX
#define FSLINUX
#include "FSWindow.h"
#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <stdint.h>

namespace FS {
class XlibWindow : public BaseWindow {
    private:
    XWindow mWindowHandle = 0;
    Display *mDisplay = nullptr;
    int mScreen = 0;
    GC mGc = nullptr;
    XImage *mBackImage = nullptr;
    Cursor defaultCursor = 0;
    Cursor hiddenCursor = 0;
    Pixmap emptyPixmap = 0;

    inline void setNative(XWindow window) { mWindowHandle = window; }

    public:
    XlibWindow(const char *name = "NULL", uint32_t width = 720,
               uint32_t height = 720);
    ~XlibWindow();

    XlibWindow(const XlibWindow&) = delete;
    XlibWindow& operator=(const XlibWindow&) = delete;
    XlibWindow(const XlibWindow&&) = delete;
    XlibWindow& operator=(const XlibWindow&&) = delete;

    void swapBuffers() override;
    void processMessages() override;
    void addConsole() const override;
    void removeConsole() const override;
    bool isOpen() const override { return static_cast<bool>(mWindowHandle); }
    bool isFocused() const override;
    void showCursor(bool show) override;
    void setWindowPos(int x, int y) override;
    void setCursorPos(uint32_t x, uint32_t y) override;
    void focus() const override;
    Vector2 getWindowPos() const override;
    Vector2 getCursorPos() const override;
    void close() override {
        if (isOpen()) {
            XDestroyWindow(mDisplay, mWindowHandle);
            mWindowHandle = (XWindow) nullptr;
        }
    }
    inline XWindow getNative() const { return mWindowHandle; }
};
} // namespace FS
#endif
#endif
