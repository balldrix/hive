#include "Window.h"
#include "Constants.h"

Window::Window() :
m_hWindow(nullptr),
m_width(0),
m_height(0)
{
}

Window::~Window()
{
}

void 
Window::Init(HINSTANCE hInstance, INT cmdShow, WNDPROC winProc)
{
	// set game dimentions
	m_width = GlobalConstants::WND_WIDTH;
	m_height = GlobalConstants::WND_HEIGHT;

	// setup window class to register window
	WNDCLASS wc = { 0 };
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = winProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = GlobalConstants::WND_CLASS_NAME;
	RegisterClass(&wc);

	// adjust window boundary to maintain game dimensions
	RECT rc = { 0, 0, (long)m_width, (long)m_height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// create window
	m_hWindow = CreateWindow(GlobalConstants::WND_CLASS_NAME,
						   GlobalConstants::WINDOW_NAME,
						   WS_OVERLAPPEDWINDOW,
						   0,
						   0,
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

	// update window
	UpdateWindow(m_hWindow);
}