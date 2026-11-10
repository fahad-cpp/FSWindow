#include "FSWindow.h"
#include <memory>
#ifdef _WIN32
#include "Win32Window.h"
namespace FS {
typedef Win32Window WindowType;
}
#elif __linux__
#include "XlibWindow.h"
namespace FS {
typedef XlibWindow WindowType;
}
#endif

FS::Window::Window(const char *name, uint32_t width, uint32_t height) : impl() {
    impl = std::make_unique<WindowType>(name, width, height);
    impl->addConsole();
}

FS::Window::~Window() = default;

FSNativeWindow FS::Window::getNative() {
    return static_cast<WindowType *>(impl.get())->getNative();
}