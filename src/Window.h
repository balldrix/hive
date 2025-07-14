#pragma once

#include <windows.h>

class Window
{
	public:
		Window();
		~Window();
		int Init(int width, int height, HINSTANCE hInstance, INT cmdShow, WNDPROC wndProc);
		HINSTANCE GetInstance() noexcept { return HINSTANCE(); }
		HWND GetHwnd() const { return m_hWindow; }

		bool GetMinimized() const { return m_minimized; }
		bool GetMaximized() const { return m_maximized; }
		bool GetResizing() const { return m_resizing; }
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }
		bool GetFullscreen() const { return m_fullscreen; }

		void SetMinimized(bool value);
		void SetMaximized(bool value);
		void SetResizing(bool value);
		void SetWidth(int width);
		void SetHeight(int height);
		void ResizeWindow(int width, int height);
		void SetFullscreen(bool fullscreen);

	private:
		HINSTANCE m_hInst;
		HWND m_hWindow;
		int m_width;
		int m_height;
		bool m_minimized;
		bool m_maximized;
		bool m_resizing;
		DWORD m_windowStyle;
		bool m_fullscreen;
};