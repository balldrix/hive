#include "Window.h"
#include "Constants.h"

using namespace GlobalConstants;

Window::Window() :
	m_hInst(nullptr),
	m_hWindow(nullptr),
	m_width(0),
	m_height(0)
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

	// adjust window boundary to maintain game dimensions
	RECT rc = { 0, 0, (long)m_width, (long)m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// create window
	m_hWindow = CreateWindow(WndClassName,
						   WindowName,
						   WS_OVERLAPPEDWINDOW,
						   300,
						   200,
						   rc.right - rc.left,
						   rc.bottom - rc.top,
						   NULL,
						   NULL,
						   hInstance,
						   NULL);
	// hide cursor
	ShowCursor(false);

	// show window
	ShowWindow(m_hWindow, cmdShow);
}

HINSTANCE Window::GetInstance() noexcept
{
	return HINSTANCE();
}
