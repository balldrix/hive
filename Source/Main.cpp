/*
	Hive v0.0.011
	using the Kaon Engine

	Christopher Ball
	Copyright (c) 2015
*/


//CRT Debug for memory leaks
#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "Hive.h"

// Windows Handle
HWND		hWindow;

// is running flag
bool		running;

// struct to deal with windows message queue
MSG msg;

// game object
Hive* game;

// Prototypes
// main entry point
int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

// create window function
bool		CreateMainWindow(HWND &hWindow, HINSTANCE hInstance, int nCmdShow);

// WinProc function to handle messages
LRESULT		WINAPI WinProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

// Initialise stuff
bool		Init(HINSTANCE hInstance, int nCmdShow);

// Entry point for program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
		// Check for memory leak if debug build
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

		// create breakpoint at num location 
		//_CrtSetBreakAlloc(249);

		if(!Init(hInstance, nCmdShow))
		{
			MessageBox(hWindow, "Failed to initalise", "Error!", MB_OK);
			return 0;
		}

	// main game loop
	while (running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				running = false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->Run(hWindow);
		}
	}

	if (game != NULL)
	{
		delete game;
		game = NULL;
		
	}

	return msg.wParam;
}

// Initialise window and its params
bool CreateMainWindow(HWND &hWindow, HINSTANCE hInstance, int nCmdShow)
{
	// Windows Class
	WNDCLASSEX	wClassex;

	// Null all class parameters
	ZeroMemory(&wClassex, sizeof(wClassex));

	wClassex.cbSize = sizeof(wClassex);
	wClassex.style = CS_CLASSDC;
	wClassex.lpfnWndProc = WinProc;
	wClassex.hInstance = hInstance;
	wClassex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClassex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wClassex.lpszClassName = CLASS_NAME;

	// Register the window class
	if (!RegisterClassEx(&wClassex))
	{
		MessageBox(hWindow, "Error Creating Window Class!", "Error!", MB_OK);
		return false;
	}

	// Style flags
	DWORD style;

	if(FULLSCREEN)
	{
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	}
	else
	{
		style = WS_OVERLAPPED; // | WS_MINIMIZEBOX | WS_SYSMENU;
	}

	// create the window
	hWindow = CreateWindow(
		CLASS_NAME,
		GAME_NAME,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GAME_WIDTH,
		GAME_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if(!hWindow)
	{
		MessageBox(hWindow, "Error Creating Window!", "Error!", MB_OK);
		return false;
	}

	if (!FULLSCREEN)
	{ 
		RECT clientRect;
		GetClientRect(hWindow, &clientRect);

		MoveWindow(hWindow, 
			0, 
			0, 
			GAME_WIDTH + (GAME_WIDTH - clientRect.right), 
			GAME_HEIGHT + (GAME_HEIGHT - clientRect.bottom), 
			TRUE);
	}

	ShowWindow(hWindow, nCmdShow);

	return true;
}

LRESULT WINAPI WinProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return (game->MessageHandler(hWindow, msg, wParam, lParam));
}

bool Init(HINSTANCE hInstance, int nCmdShow)
{
	hWindow = NULL;
	running = true;

	game = NULL;
	game = new Hive;

	// create a window
	if (!CreateMainWindow(hWindow, hInstance, nCmdShow))
	{
		return false;
	}

	game->Init(hWindow);
		
	return true;
}