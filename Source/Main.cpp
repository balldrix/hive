// Main.cpp
// Hive Project
// Christopher Ball 2018

#include "Window.h"
#include "Graphics.h"
#include "Game.h"

// Global Variables
Graphics* graphics = nullptr;
Window* window	= nullptr;
Game* game = nullptr;

// Prototype Functions
void ShutDown();

// WndProc call back needed for windows messages like key and mouse input
LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE pPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	// initialise Window
	window = new Window();
	window->Init(hInstance, nCmdShow, WndProc);
	
	// initialise graphics
	graphics = new Graphics();
	graphics->Init(window->GetHwnd(), hInstance);

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
	
	CoUninitialize();
}

LRESULT CALLBACK
WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// send message handler from game engine to WndProc callback function
	return game->MessageHandler(hWindow, msg, wParam, lParam);
}