#include "Window.h"
#include "Constants.h"

using namespace GlobalConstants;

Window::Window() :
	m_hInst(nullptr),
	m_hWindow(nullptr),
	m_width(0),
	m_height(0),
	m_minimized(false),
	m_maximized(false),
	m_resizing(false)
{
}
	
Window::~Window()
{
	UnregisterClass(WndClassName, GetInstance());
	DestroyWindow(m_hWindow);
}


void Window::Init(HINSTANCE hInstance, INT cmdShow, WNDPROC winProc)
{
	m_hInst = GetModuleHandle(nullptr);
	m_width = WindowWidth;
	m_height = WindowHeight;

	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = winProc;
	wcx.hInstance = hInstance;
	wcx.lpszClassName = WndClassName;
	RegisterClassEx(&wcx);

	RECT rc = { 0, 0, (long)m_width + rc.left, (long)m_height + rc.top };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWindow = CreateWindow(
		WndClassName, WindowName, 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInstance,
		this);

	ShowCursor(true);
	ShowWindow(m_hWindow, cmdShow);
}

HINSTANCE Window::GetInstance() noexcept
{
	return HINSTANCE();
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
