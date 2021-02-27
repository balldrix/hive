#include "Game.h"

#include "pch.h"
#include "Window.h"
#include "Graphics.h"
#include "Input.h"

#include "GameStateManager.h"
#include "GameState.h"

#include "GameplayGameState.h"

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

LRESULT Game::MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(this == nullptr)
		return DefWindowProc(hWindow, msg, wParam, lParam);

	// handle msg values in switch statement
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0); // post quit window
			break;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:
			m_input->SetKeyDown(wParam); // set keyboard key down
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
			// Save the new client area dimensions.
			m_clientWidth = LOWORD(lParam);
			m_clientHeight = HIWORD(lParam);

			if(m_graphics != nullptr && m_graphics->GetDevice() != nullptr)
			{
				if(wParam == SIZE_MINIMIZED)
				{
					m_paused = true;
					m_window->SetMinimized(true);
					m_window->SetMaximized(false);
				}
				else if(wParam == SIZE_MAXIMIZED)
				{
					m_paused = false;
					m_window->SetMinimized(false);
					m_window->SetMaximized(true);
					m_graphics->CreateResources(m_clientWidth, m_clientHeight);
				}
				else if(wParam == SIZE_RESTORED)
				{
					if(m_window->GetMinimized() == true)
					{
						m_paused = false;
						m_window->SetMinimized(false);
						m_graphics->CreateResources(m_clientWidth, m_clientHeight);
					}

					// Restoring from maximized state?
					else if(m_window->GetMaximized() == true)
					{
						m_paused = false;
						m_window->SetMaximized(false);
						m_graphics->CreateResources(m_clientWidth, m_clientHeight);
					}
					else if(m_window->GetResizing())
					{
						// If user is dragging the resize bars, we do not resize 
						// the buffers here because as the user continuously 
						// drags the resize bars, a stream of WM_SIZE messages are
						// sent to the window, and it would be pointless (and slow)
						// to resize for each WM_SIZE message received from dragging
						// the resize bars.  So instead, we reset after the user is 
						// done resizing the window and releases the resize bars, which 
						// sends a WM_EXITSIZEMOVE message.
					}
					else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
					{
						m_graphics->CreateResources(m_clientWidth, m_clientHeight);
					}
				}
			}
			break;
		case WM_ENTERSIZEMOVE:
			m_paused = true;
			m_window->SetResizing(true);
			return 0;
		case WM_EXITSIZEMOVE:
			m_paused = false;
			m_window->SetResizing(false);
			if(m_graphics != nullptr) 
				m_graphics->CreateResources(m_clientWidth, m_clientHeight);
			break;
	}

	return DefWindowProc(hWindow, msg, wParam, lParam);
}