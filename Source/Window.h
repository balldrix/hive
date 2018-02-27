// Window.h
// Christopher Ball 2018
// This class encapsulates the window creation
// and hides away the WndProc function

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "pch.h"

class Window
{
	public:
		Window();
		~Window();
		void Init(HINSTANCE hInstance, INT cmdShow, WNDPROC winProc); // initialise window
		HWND GetHwnd() { return m_hWindow; } // get handle to window

	private:
		HWND m_hWindow; // window handle
		unsigned int m_width; // width of window
		unsigned int m_height; // height of window
};


#endif _WINDOW_H_