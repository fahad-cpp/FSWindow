#include "FSWindow.h"
#include <memory>
#ifdef _WIN32
#include "Win32Window.h"
#elif __linux__
#include "XlibWindow.h"
#endif

FS::Window::Window(const char *name, uint32_t width, uint32_t height) : impl() {
#ifdef _WIN32
    impl = std::make_unique<Win32Window>(name, width, height);
#elif __linux__
    impl = std::make_unique<XlibWindow>(name, width, height);
#endif
    impl->addConsole();
}

FS::Window::~Window() = default;

#ifdef _WIN32
HWND FS::Window::getNative() {
    return static_cast<Win32Window *>(impl.get())->getNative();
}
#elif __linux__
XWindow FS::Window::getNative() {
    return static_cast<XlibWindow *>(impl.get())->getNative();
}
#endif
