// Window.h
// Christopher Ball 2019
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
		HINSTANCE GetInstance() noexcept;
		HWND GetHwnd() const { return m_hWindow; }
	private:
		HINSTANCE m_hInst;
		HWND m_hWindow;
		int m_width;
		int m_height;
};

#endif _WINDOW_H_