#pragma once

#include <windows.h>

class Window
{
	public:
		Window();
		~Window();
		int Init(HINSTANCE hInstance, INT cmdShow, WNDPROC wndProc);
		HINSTANCE GetInstance() noexcept { return HINSTANCE(); }
		HWND GetHwnd() const { return m_hWindow; }

		bool GetMinimized() const { return m_minimized; }
		bool GetMaximized() const { return m_maximized; }
		bool GetResizing() const { return m_resizing; }
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		void SetMinimized(bool value);
		void SetMaximized(bool value);
		void SetResizing(bool value);
		void SetWidth(int width);
		void SetHeight(int height);

	private:
		HINSTANCE m_hInst;
		HWND m_hWindow;
		int m_width;
		int m_height;
		bool m_minimized;
		bool m_maximized;
		bool m_resizing;
};