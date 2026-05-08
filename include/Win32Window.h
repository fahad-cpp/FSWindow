#ifndef FSWIN32
#define FSWIN32
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Window.h"
namespace FS {
	//WIN32 window
	class Win32Window : public BaseWindow {
	private:
		HWND mWindowHandle;
		HDC mDeviceContextHandle;

		inline void setNative(HWND window) { mWindowHandle = window; }
		inline HWND getNative() const { return mWindowHandle; }
	public:
		BITMAPINFO bitmapInfo;
		Win32Window(const char* name = "NULL", uint32_t width = 720, uint32_t height = 720);
		~Win32Window();
		void swapBuffers() override;
		void processMessages() override;
		void addConsole() const override;
		void removeConsole() const override;
		bool isOpen() const override { return IsWindow(mWindowHandle); }
		void showCursor(bool show);
		void setWindowPos(uint32_t x, uint32_t y);
		void setCursorPos(uint32_t x, uint32_t y);
		Vector2 getWindowPos() const override;
		Vector2 getCursorPos() const override;
		void close() override;
	};
};
#endif
#endif