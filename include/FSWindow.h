#ifndef FSWINDOW
#define FSWINDOW
#include <iostream>
#include <string>
#include <stdint.h>
#include "Input.h"
struct RenderState {
	int width;
	int height;
	void* screenBuffer;
	float* depthBuffer;
};
class BaseWindow {
public:
	RenderState renderState;
	Input input;
	virtual void swapBuffers() = 0;
	virtual void processMessages() = 0;
	virtual void addConsole() const = 0;
	virtual void removeConsole() const = 0;
	virtual bool isOpen() const = 0;
	virtual void showCursor(bool show) = 0;
	virtual void setWindowPos(uint32_t x,uint32_t y) = 0;
	virtual void setCursorPos(uint32_t x,uint32_t y) = 0;
	virtual void close() = 0;
	virtual inline RenderState* getRenderState() { return  &renderState; }
	virtual inline Input* getInput() { return &input; }
};

//interface Class
class FSWindow {
private:
	BaseWindow* impl;
public:
	FSWindow(const char* name = "NULL", uint32_t width = 720, uint32_t height = 720);
	~FSWindow();
	inline void swapBuffers() { impl->swapBuffers(); }
	inline void processMessages() { impl->processMessages(); }
	inline void addConsole() const { impl->addConsole(); };
	inline void removeConsole() const { impl->removeConsole(); };
	inline bool isOpen() const { return impl->isOpen(); };
	inline void showCursor(bool show){impl->showCursor(show);}
	inline void setWindowPos(uint32_t x,uint32_t y){impl->setWindowPos(x,y);}
	inline void setCursorPos(uint32_t x,uint32_t y){impl->setCursorPos(x,y);}
	inline void close() { return impl->close(); };
	inline RenderState* getRenderState() { return impl->getRenderState(); };
	inline Input* getInput() { return impl->getInput(); }
};
#endif