#include "FSWindow.h"
#ifdef _WIN32
#include "Win32Window.h"
#elif __linux__
#include "XlibWindow.h"
#endif

FS::Window::Window(const char *name, uint32_t width, uint32_t height) {
#ifdef _WIN32
    impl = new Win32Window(name, width, height);
#elif __linux__
    impl = new XlibWindow(name, width, height);
#endif
    impl->addConsole();
}

FS::Window::~Window() {
#ifdef _WIN32
    delete (Win32Window *)impl;
#elif __linux__
    delete (XlibWindow *)impl;
#endif
}

#ifdef _WIN32
HWND FS::Window::getNative() {
    return static_cast<Win32Window *>(impl)->getNative();
}
#elif __linux__
XWindow FS::Window::getNative() {
    return static_cast<XlibWindow *>(impl)->getNative();
}
#endif
