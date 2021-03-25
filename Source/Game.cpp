#include "Game.h"

#include "pch.h"
#include "Window.h"
#include "Graphics.h"
#include "Input.h"

#include "GameStateManager.h"
#include "GameState.h"

#include "GameplayGameState.h"
#include "Constants.h"

using namespace GlobalConstants;

Game::Game() :
	m_window(nullptr),
	m_graphics(nullptr),
	m_spriteBatch(nullptr),
	m_input(nullptr),
	m_gameStateManager(nullptr),
	m_timerFreq(0.0f),
	m_gameTime(0.0f),
	m_currentTime(0.0f),
	m_retryAudio(false),
	m_clientWidth(0),
	m_clientHeight(0)
{
}

Game::~Game()
{
	DeleteAll(); // delete all pointers
}

void Game::Init(Window* window, Graphics* graphics)
{
	// allow multi threading
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	m_window = window;
	m_graphics = graphics;

	m_input = new Input();

	m_gameStateManager = new GameStateManager();
	m_gameStateManager->Init(m_graphics,
							 m_input);

	m_gameStateManager->AddState(new GameplayGameState(m_gameStateManager));
	m_gameStateManager->SwitchState(L"GAMEPLAY");

	m_timerFreq = m_timer.GetFrequency();
	m_currentTime = m_timer.GetTicks();
	m_paused = false;
}

void Game::Run()
{
	float newTime = m_timer.GetTicks();
	float deltaTime = (newTime - m_currentTime) * m_timerFreq;

	m_currentTime = newTime;

	if(m_paused == false)
	{
		ProcessInput();
		Update(deltaTime);
		Render();
		ProcessCollisions();
	}
	else
	{
		deltaTime = 0.0f;
		Sleep(100);
	}

	m_gameTime += deltaTime;
	m_input->ClearKeysPressed();
}

void Game::ProcessInput()
{
	m_gameStateManager->ProcessInput();
}

void Game::Update(float deltaTime)
{
	m_gameStateManager->Update(deltaTime);
}

void Game::ProcessCollisions()
{
	m_gameStateManager->ProcessCollisions();
}

void Game::Render()
{
	m_graphics->BeginScene();
	m_gameStateManager->Render();
	m_graphics->PresentBackBuffer();
}

void Game::ReleaseAll()
{
	m_graphics->ReleaseAll();
	m_gameStateManager->ReleaseAll();
}

void Game::DeleteAll()
{
	if(m_gameStateManager)
	{
		delete m_gameStateManager;
		m_gameStateManager = nullptr;
	}

	if(m_input)
	{
		delete m_input;
		m_input = nullptr;
	}

	if(m_graphics)
	{
		m_graphics = nullptr;
	}

	if(m_window)
	{
		m_window = nullptr;
	}
}

void Game::OnSuspending()
{
}

void Game::OnResuming()
{
}

void Game::OnWindowSizeChanged(int width, int height)
{
	m_graphics->CreateResources(width, height);
}

LRESULT Game::MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool s_in_sizemove = false;
	static bool s_in_suspend = false;
	static bool s_minimized = false;
	static bool s_fullscreen = false;

	// handle msg values in switch statement
	switch(msg)
	{
		case WM_PAINT:
			if(s_in_sizemove && this != nullptr)
			{
				Run();
			}
			else
			{
				PAINTSTRUCT ps;
				(void) BeginPaint(hWindow, &ps);
				EndPaint(hWindow, &ps);
			}
		break;

		case WM_DESTROY:
			PostQuitMessage(0); // post quit window
			break;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:
			m_input->SetKeyDown(wParam); // set keyboard key down

			if(wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
			{
				// Implements the classic ALT+ENTER fullscreen toggle
				if(s_fullscreen)
				{
					SetWindowLongPtr(hWindow, GWL_STYLE, WS_OVERLAPPEDWINDOW);
					SetWindowLongPtr(hWindow, GWL_EXSTYLE, 0);

					int width = WindowWidth;
					int height = WindowHeight;

					ShowWindow(hWindow, SW_SHOWNORMAL);

					SetWindowPos(hWindow, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
				}
				else
				{
					SetWindowLongPtr(hWindow, GWL_STYLE, 0);
					SetWindowLongPtr(hWindow, GWL_EXSTYLE, WS_EX_TOPMOST);

					SetWindowPos(hWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

					ShowWindow(hWindow, SW_SHOWMAXIMIZED);
				}

				s_fullscreen = !s_fullscreen;
			}

			break;
		case WM_KEYUP: case WM_SYSKEYUP:
			m_input->SetKeyUp(wParam); // set keyboard key up
			break;
		case WM_MOUSEMOVE:
			m_input->SetMouseIn(lParam); // set mouse position
			break;
		case WM_LBUTTONDOWN:
			m_input->SetMouseClicked(true);
			m_input->SetMouseIn(lParam);
			break;
		case WM_LBUTTONUP:
			m_input->SetMouseClicked(false);
			m_input->SetMouseIn(lParam);
			break;
		case WM_SIZE:
			if(wParam == SIZE_MINIMIZED)
			{
				if(!s_minimized)
				{
					s_minimized = true;
					if(!s_in_suspend && this != nullptr)
						OnSuspending();
					s_in_suspend = true;
				}
			}
			else if(s_minimized)
			{
				s_minimized = false;
				if(s_in_suspend && this != nullptr)
					OnResuming();
				s_in_suspend = false;
			}
			else if(!s_in_sizemove && this != nullptr)
			{
				OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
			}			
			break;
		case WM_ENTERSIZEMOVE:
			m_paused = true;
			s_in_sizemove = true;
			return 0;
		case WM_EXITSIZEMOVE:
			m_paused = false;
			s_in_sizemove = false;

			RECT rc;
			GetClientRect(hWindow, &rc);

			if(m_graphics != nullptr)
				m_graphics->CreateResources(rc.right - rc.left, rc.bottom - rc.top);
			break;
	}

	return DefWindowProc(hWindow, msg, wParam, lParam);
}