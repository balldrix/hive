#include "Game.h"

#include "pch.h"
#include "Graphics.h"
#include "Input.h"

#include "GameStateManager.h"
#include "GameState.h"

#include "MenuGameState.h"
#include "GameplayGameState.h"

Game::Game() :
	m_graphics(nullptr),
	m_input(nullptr),
	m_gameStateManager(nullptr),
	m_timerFreq(0.0f),
	m_currentTime(0.0f),
	m_previousTime(0.0f),
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
	m_gameStateManager->AddState(new MenuGameState(m_gameStateManager));
	m_gameStateManager->AddState(new GameplayGameState(m_gameStateManager));
	m_gameStateManager->SwitchState(L"MENU");

	// get cpu frequency and current time in ticks
	m_timerFreq = m_timer.GetFrequency();
	m_currentTime = m_timer.GetTicks();
}

void
Game::Run()
{
	m_previousTime = m_currentTime; // keep current time for next update
	m_currentTime = m_timer.GetTicks(); // get cpu tick count
	float deltaTime = (m_currentTime - m_previousTime) * m_timerFreq; // calculate time taken since last update

	// if delta time becomes too large
	// lock at 60fps
	if(deltaTime > 0.016f)
	{
		deltaTime = 0.016f;
	}

	ProcessInput(); // read key and mouse input into game
	Update(deltaTime); // update game
	Render(); // render objects	
}

void
Game::ProcessInput()
{
	// process game state input
	m_gameStateManager->ProcessInput();
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

void
Game::ReleaseAll()
{
	m_graphics->ReleaseAll(); // release all graphics related pointers
	m_gameStateManager->ReleaseAll(); // release all states
	m_audio.reset(); // reset audio engine
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