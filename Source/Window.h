// Window.h
// Christopher Ball 2019-2021

#pragma once

#include "pch.h"

class Window
{
	public:
		Window();
		~Window();
		void Init(HINSTANCE hInstance, INT cmdShow, WNDPROC winProc);
		HINSTANCE GetInstance() noexcept;
		HWND GetHwnd() const { return m_hWindow; }

		bool GetMinimized() const { return m_minimized; }
		bool GetMaximized() const { return m_maximized; }
		bool GetResizing() const { return m_resizing; }

		void SetMinimized(bool value);
		void SetMaximized(bool value);
		void SetResizing(bool value);

	private:
		HINSTANCE m_hInst;
		HWND m_hWindow;
		int m_width;
		int m_height;
		bool m_minimized;
		bool m_maximized;
		bool m_resizing;
};