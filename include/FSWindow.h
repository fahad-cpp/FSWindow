#ifndef WINDOW_H
#define WINDOW_H
#include "Input.h"
#include "Vector2.h"
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <X11/Xlib.h>
typedef Window XWindow;
#endif
namespace FS {
struct RenderState {
    int width;
    int height;
    void *screenBuffer;
    float *depthBuffer;
};
class BaseWindow {
  public:
    RenderState renderState = {};
    Input input = {};
    virtual void swapBuffers() = 0;
    virtual void processMessages() = 0;
    virtual void addConsole() const = 0;
    virtual void removeConsole() const = 0;
    virtual bool isOpen() const = 0;
    virtual void showCursor(bool show) = 0;
    virtual void setWindowPos(int x, int y) = 0;
    virtual void setCursorPos(uint32_t x, uint32_t y) = 0;
    virtual Vector2 getWindowPos() const = 0;
    virtual Vector2 getCursorPos() const = 0;
    virtual void close() = 0;
    virtual inline RenderState& getRenderState() { return renderState; }
    virtual inline Input& getInput() { return input; }
};

class Window {
  private:
    BaseWindow *impl;

  public:
    Window(const char *name = "NULL", uint32_t width = 720, uint32_t height = 720);
    ~Window();
    inline void swapBuffers() { impl->swapBuffers(); }
    inline void processMessages() { impl->processMessages(); }
    inline void addConsole() const { impl->addConsole(); };
    inline void removeConsole() const { impl->removeConsole(); };
    inline bool isOpen() const { return impl->isOpen(); };
    inline void showCursor(bool show) { impl->showCursor(show); }
    inline void setWindowPos(int x, int y) { impl->setWindowPos(x, y); }
    inline void setCursorPos(uint32_t x, uint32_t y) { impl->setCursorPos(x, y); }
    inline Vector2 getWindowPos() const { return impl->getWindowPos(); }
    inline Vector2 getCursorPos() const { return impl->getCursorPos(); }
    inline void close() { return impl->close(); };
    inline RenderState& getRenderState() { return impl->getRenderState(); };
    inline Input& getInput() { return impl->getInput(); }
#ifdef _WIN32
    HWND getNative();
#elif __linux__
    XWindow getNative();
#endif
};
}; // namespace FS

#endif
