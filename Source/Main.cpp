/*
	Hive v0.0.011
	using the Kaon Engine

	Christopher Ball
	Copyright (c) 2016
*/

//CRT Debug for memory leaks
#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN

#include "Window.h"
#include "Graphics.h"
#include "Hive.h"

// Global Variables
Graphics* graphics = nullptr;
Window* window	= nullptr;
Game* game = nullptr;

// Prototypes
// main entry point
int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

// WinProc function to handle messages
LRESULT		WINAPI WinProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

// Entry point for program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
		// Check for memory leak if debug build
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

		// initialise Window
		window = new Window();
		window->Init(hInstance, nCmdShow, WndProc);

		// initialise graphics
		graphics = new Graphics();
		graphics->Init(window->GetHwnd());

		// initialise game engine
		game = new Game();
		game->Init(graphics);

		// start message processes where the magic happens
		MSG msg = {0};

		while(msg.message != WM_QUIT)
		{
			// peek at windows message queue 
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// run game
				game->Run();
			}
		}

		// release game related objects and delete pointers
		game->ReleaseAll(); 
		ShutDown();

		return (int)msg.wParam;
}

void ShutDown()
{
	if(game)
	{
		// delete game class and null pointer
		delete game;
		game = nullptr;
	}

	if(graphics)
	{
		// delete graphics class and null pointer
		delete graphics;
		graphics = nullptr;
	}

	if(window)
	{
		// delete window class and null pointer
		delete window;
		window = nullptr;
	}
}

LRESULT CALLBACK
WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// send message handler from game engine to WndProc callback function
	return game->MessageHandler(hWindow, msg, wParam, lParam);
}