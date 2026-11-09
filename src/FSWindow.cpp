#include "FSWindow.h"
#include <memory>
#ifdef _WIN32
#include "Win32Window.h"
typedef FS::Win32Window WindowType;
#elif __linux__
#include "XlibWindow.h"
typedef FS::XlibWindow WindowType;
#endif

FS::Window::Window(const char *name, uint32_t width, uint32_t height) : impl() {
    impl = std::make_unique<WindowType>(name, width, height);
    impl->addConsole();
}

FS::Window::~Window() = default;

NativeWindow FS::Window::getNative() {
    return static_cast<WindowType *>(impl.get())->getNative();
}