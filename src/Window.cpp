#include "Window.h"

#include "GlobalConstants.h"
#include "Logger.h"

using namespace GlobalConstants;

Window::Window() :
	m_hInst(nullptr),
	m_hWindow(nullptr),
	m_width(WindowWidth),
	m_height(WindowHeight),
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


int Window::Init(HINSTANCE hInstance, INT cmdShow, WNDPROC wndProc)
{
	m_hInst = hInstance;

    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
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

    m_hWindow = CreateWindowExW(0, WndClassName, WindowName, WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                                nullptr);
    // TODO: Change to CreateWindowExW(WS_EX_TOPMOST, L"Direct3D_Win32_Game1WindowClass", L"Direct3D Win32 Game1", WS_POPUP,
    // to default to fullscreen.

    if(!m_hWindow)
        return 1;

    ShowWindow(m_hWindow, cmdShow);
    // TODO: Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.

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
