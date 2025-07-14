#include "Window.h"

#include "GlobalConstants.h"
#include "Logger.h"
#include "SettingsManager.h"

using namespace GlobalConstants;

Window::Window() :
	m_hInst(nullptr),
	m_hWindow(nullptr),
	m_width(0),
	m_height(0),
	m_minimized(false),
	m_maximized(false),
	m_resizing(false),
	m_windowStyle(0),
	m_fullscreen(false)
{
}
	
Window::~Window()
{
	UnregisterClass(WndClassName, GetInstance());
	DestroyWindow(m_hWindow);
}


int Window::Init(int width, int height, HINSTANCE hInstance, INT cmdShow, WNDPROC wndProc)
{
	m_windowStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	m_width = width;
	m_height = height;
	m_hInst = hInstance;
	m_fullscreen = SettingsManager::Instance()->IsFullscreen();

	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIconW(hInstance, L"IDI_ICON");
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszClassName = WndClassName;
	wcex.hIconSm = LoadIconW(wcex.hInstance, L"IDI_ICON");
	if(!RegisterClassExW(&wcex))
		return 1;

	RECT rc = { 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWindow = CreateWindowExW(0, WndClassName, WindowName, m_windowStyle,
								CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
								nullptr);

	if(!m_hWindow)
		return 1;

	SetFullscreen(m_fullscreen);

	GetClientRect(m_hWindow, &rc);

	Logger::LogInfo("Initialised Window.");

	return 0;
}

void Window::SetMinimized(bool value)
{
	m_minimized = value;
}

void Window::SetMaximized(bool value)
{
	m_maximized = value;
}

void Window::SetResizing(bool value)
{
	m_resizing = value;
}

void Window::SetWidth(int width)
{
	m_width = width;
}

void Window::SetHeight(int height)
{
	m_height = height;
}

void Window::ResizeWindow(int width, int height)
{
	m_width = width;
	m_height = height;

	RECT rc = { 0, 0, m_width, m_height };
	AdjustWindowRect(&rc, m_windowStyle, FALSE);
	int windowWidth = rc.right - rc.left;
	int windowHeight = rc.bottom - rc.top;

	SetWindowPos(m_hWindow, nullptr, CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, SWP_NOMOVE | SWP_NOZORDER);
}

void Window::SetFullscreen(bool fullscreen)
{
	m_fullscreen = fullscreen;

	if(!fullscreen)
	{
		SetWindowLongPtr(m_hWindow, GWL_STYLE, m_windowStyle);
		SetWindowLongPtr(m_hWindow, GWL_EXSTYLE, 0);

		int width = SettingsManager::Instance()->GetScreenWidth();
		int height = SettingsManager::Instance()->GetScreenHeight();

		ShowWindow(m_hWindow, SW_SHOWNORMAL);
		SetWindowPos(m_hWindow, HWND_TOP, CW_USEDEFAULT, CW_USEDEFAULT, width, height, SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowLongPtr(m_hWindow, GWL_STYLE, 0);
		SetWindowLongPtr(m_hWindow, GWL_EXSTYLE, WS_EX_TOPMOST);

		SetWindowPos(m_hWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOZORDER);
		ShowWindow(m_hWindow, SW_SHOWMAXIMIZED);
	}
}
