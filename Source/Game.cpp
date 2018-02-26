#include "Game.h"

#include "pch.h"
#include "Graphics.h"
#include "Input.h"
#include "Controls.h"

#include "GameStateManager.h"
#include "GameState.h"

#include "GameplayGameState.h"

Game::Game() :
	m_graphics(nullptr),
	m_input(nullptr),
	m_gameStateManager(nullptr),
	m_timerFreq(0.0f),
	m_gameTime(0.0f),
	m_currentTime(0.0f),
	m_retryAudio(false)
{
}

Game::~Game()
{
	DeleteAll(); // delete all pointers
}

void
Game::Init(Graphics* graphics)
{
	// allow multi threading
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	m_graphics = graphics; // copy pointer address to 

	// create new input class
	m_input = new Input();

	// create new game state manager
	m_gameStateManager = new GameStateManager();
	m_gameStateManager->Init(m_graphics,
							 m_input);

	// add game states to state list and switch to front end
	m_gameStateManager->AddState(new GameplayGameState(m_gameStateManager));
	m_gameStateManager->SwitchState(L"GAMEPLAY");

	// get cpu frequency and current time in ticks
	m_timerFreq = m_timer.GetFrequency();
	m_currentTime = m_timer.GetTicks();
}

void
Game::Run()
{
	float newTime = m_timer.GetTicks(); // get cpu tick count
	float deltaTime = (newTime - m_currentTime) * m_timerFreq; // calculate time taken since last update

	m_currentTime = newTime; // keep current time for next update

	ProcessInput();			// read key and mouse input into game
	Update(deltaTime);		// update game

	m_gameTime += deltaTime; // increment game time

	Render();				// render objects	

	m_input->ClearKeysDown(); // clear keys pressed
}

void
Game::ProcessInput()
{
	// process game state input
	m_gameStateManager->ProcessInput();

	// if Alt+Enter toggle fullscreen/window
	if(m_input->IsKeyDown(ALT_KEY) && m_input->WasKeyPressed(ENTER_KEY))
	{
		SetDisplayMode(DisplayMode::FULLSCREEN); // toggle fullscreen/window
	}
}

void
Game::Update(float deltaTime)
{
	// update game state
	m_gameStateManager->Update(deltaTime);
}

void
Game::Render()
{
	// prepare graphics render target and clear backbuffer
	m_graphics->BeginScene();

	// render game state
	m_gameStateManager->Render();

	// display backbuffer on screen
	m_graphics->PresentBackBuffer();
}

void Game::SetDisplayMode(DisplayMode mode)
{
	ReleaseAll();
	m_graphics->ChangeDisplayMode(mode);
}

void
Game::ReleaseAll()
{
	m_graphics->ReleaseAll(); // release all graphics related pointers
	m_gameStateManager->ReleaseAll(); // release all states
}

void
Game::DeleteAll()
{
	// delete game state manager
	if(m_gameStateManager)
	{
		delete m_gameStateManager;
		m_gameStateManager = nullptr;
	}

	// delete input object
	if(m_input)
	{
		delete m_input;
		m_input = nullptr;
	}

	// clear graphics object pointer
	if(m_graphics)
	{
		m_graphics = nullptr;
	}
}

LRESULT
Game::MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// handle msg values in switch statement
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0); // post quit window
			return 0;
		case WM_KEYDOWN: case WM_SYSKEYDOWN:
			m_input->SetKeyDown(wParam); // set keyboard key down
			return 0;
		case WM_KEYUP: case WM_SYSKEYUP:
			m_input->SetKeyUp(wParam); // set keyboard key up
			return 0;
		case WM_MOUSEMOVE:
			m_input->SetMouseIn(lParam); // set mouse position
			return 0;
		case WM_LBUTTONDOWN:
			m_input->SetMouseClicked(true);
			m_input->SetMouseIn(lParam);
			return 0;
		case WM_LBUTTONUP:
			m_input->SetMouseClicked(false);
			m_input->SetMouseIn(lParam);
			return 0;
	}
	// else return default
	return DefWindowProc(hWindow, msg, wParam, lParam);
}