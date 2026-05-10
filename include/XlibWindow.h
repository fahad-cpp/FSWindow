#ifndef FSLINUX
#define FSLINUX
#ifdef __linux__
#include "FSWindow.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <stdint.h>
#include "Input.h"
typedef Window XWindow;
namespace FS {
	class XlibWindow : public BaseWindow {
	private:
		XWindow mWindowHandle;
		Display* mDisplay;
		int	mScreen;
		GC mGc;
		XImage* mBackImage = nullptr;
		Cursor defaultCursor;
		Cursor hiddenCursor;
		Pixmap emptyPixmap;

		inline void setNative(XWindow window) { mWindowHandle = window; }
		inline XWindow getNative() const { return mWindowHandle; }
	public:
		XlibWindow(const char* name = "NULL", uint32_t width = 720, uint32_t height = 720);
		~XlibWindow();
		void swapBuffers() override;
		void processMessages() override;
		void addConsole() const override;
		void removeConsole() const override;
		bool isOpen() const override { return mWindowHandle; }
		void showCursor(bool show) override;
		void setWindowPos(uint32_t x, uint32_t y) override;
		void setCursorPos(uint32_t x, uint32_t y) override;
		Vector2 getWindowPos() const override;
		Vector2 getCursorPos() const override;
		void close() override { XDestroyWindow(mDisplay, mWindowHandle);mWindowHandle = (XWindow)NULL; }
	};
}
#endif
#endif