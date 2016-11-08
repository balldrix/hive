#include "Game.h"
#include "Input.h"
#include "GameStateManager.h"
#include "FrontEnd.h"
#include "ControlScreen.h"
#include "Running.h"
#include "GameOver.h"
#include "GameState.h"
#include "Constants.h"

Game::Game() :
	m_stateManager(NULL),
	m_pGraphics(NULL),
	m_pInput(NULL),
	m_hWindow(0),
	m_result(0),
	m_timeStart(0),
	m_timeEnd(0),
	m_timeFreq(0),
	m_deltaTime(0),
	m_sleepTime(0),
	m_initialised(false)
{

}

Game::~Game()
{
	ReleaseAll();
	DeleteAll();
	ShowCursor(true);
}

void
Game::Init(Graphics* graphics)
{
	// copy graphics pointer
	m_pGraphics = graphics;

	m_pInput = new Input();

	// initialise input 
	m_pInput->Init(m_hWindow, false);

	// set timer frequency
	m_timeFreq = m_pTimer.GetFrequency();

	// set timer start
	m_timeStart = m_pTimer.GetTicks();

	// create state manager object and add game states needed for game
	m_stateManager = new GameStateManager();
	m_stateManager->CreateGlobalSystems(m_pGraphics->GetHwnd(), m_pGraphics, m_pInput);
	m_stateManager->AddState(new FrontEnd(m_stateManager));
	m_stateManager->AddState(new ControlScreen(m_stateManager));
	m_stateManager->AddState(new Running(m_stateManager));
	m_stateManager->AddState(new GameOver(m_stateManager));
	m_stateManager->SwitchState("RUNNING");

	m_initialised = true;

	// seed the randoms with the current time
	srand((int)time(NULL));
}

// run method called in winmain message loop
void
Game::Run()
{
	if (m_pGraphics != NULL)
	{
		m_timeEnd = m_pTimer.GetTicks();

		m_deltaTime = ((float)(m_timeEnd - m_timeStart) / (float)m_timeFreq);

		if (m_deltaTime < GlobalConstants::MIN_FRAME_TIME)
		{
			m_sleepTime = (DWORD)((GlobalConstants::MIN_FRAME_TIME - m_deltaTime) * 1000);
			timeBeginPeriod(1);
			Sleep(m_sleepTime);
			timeEndPeriod(1);
			return;
		}

		if (m_deltaTime > 0.0)
		{
			m_fps = (m_fps * 0.99f) + (0.01f / m_deltaTime);
		}

		if (m_deltaTime > GlobalConstants::MAX_FRAME_TIME)
		{
			m_deltaTime = GlobalConstants::MAX_FRAME_TIME;
		}

		m_timeStart = m_timeEnd;

		// if Alt+Enter toggle fullscreen/window
		if (m_pInput->IsKeyDown(ALT_KEY) && m_pInput->WasKeyPressed(ENTER_KEY))
		{
			SetDisplayMode(TOGGLE); // toggle fullscreen/window
		}

		if (m_pInput->IsKeyDown(ESC_KEY))
		{
			Exit();
		}

		Update(m_deltaTime);	

		RenderGame();
		
		m_pInput->Clear(inputNS::KEYS_PRESSED);
	}
}

// delete reserved memory
void
Game::DeleteAll()
{	
	if (m_pInput != NULL)
	{
		delete m_pInput;
		m_pInput = NULL;
	}

	if (m_pGraphics != NULL)
	{
		delete m_pGraphics;
		m_pGraphics = NULL;
	}

	if (m_stateManager != NULL)
	{
		delete m_stateManager;
		m_stateManager = NULL;
	}

	m_initialised = false;
}

void
Game::Update(float deltaTime)
{
	m_stateManager->Update(deltaTime);
}

// render game objects
void
Game::Render()
{
	m_result = m_pGraphics->BeginScene();

	if (m_result == S_OK)
	{
		m_stateManager->Render();
		m_pGraphics->EndScene();
	}	
	
	HandleLostDevice();
	
	m_pGraphics->PresentBackBuffer();
}

// handle lost graphics device
void
Game::HandleLostDevice()
{
	m_result = m_pGraphics->GetDeviceState();
	if (m_result != D3D_OK)
	{
		// TODO insert error logging
		if (m_result == D3DERR_DEVICELOST)
		{
			Sleep(100);
			return;
		}
		else if (m_result == D3DERR_DEVICENOTRESET)
		{
			ReleaseAll();
			m_result = m_pGraphics->Reset();
			if (m_result != D3D_OK)
			{
				return;
			}
		}
		else
		{
			return;
		}
	}
}

void			
Game::SetDisplayMode(DisplayMode mode)
{
	ReleaseAll();
	m_pGraphics->ChangeDisplayMode(mode);
	ResetAll();
}

void
Game::ReleaseAll()
{

}

void 
Game::ResetAll()
{

}


LRESULT
Game::MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_initialised)
	{
		switch (msg)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_KEYDOWN: case WM_SYSKEYDOWN:
				m_pInput->KeyDown(wParam);
				return 0;
			case WM_KEYUP: case WM_SYSKEYUP:
				m_pInput->KeyUp(wParam);
				return 0;
			case WM_CHAR:
				m_pInput->KeyIn(wParam);
				return 0;
			case WM_MOUSEMOVE:
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_INPUT:
				m_pInput->MouseRawIn(lParam);
				return 0;
			case WM_LBUTTONDOWN:
				m_pInput->SetMouseClicked(true);
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_LBUTTONUP:
				m_pInput->SetMouseClicked(false);
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_RBUTTONDOWN:
				m_pInput->SetMouseRButton(true);
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_RBUTTONUP:
				m_pInput->SetMouseRButton(false);
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_MBUTTONDOWN:
				m_pInput->SetMouseMButton(true);
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_MBUTTONUP:
				m_pInput->SetMouseMButton(false);
				m_pInput->MouseIn(lParam);
				return 0;
			case WM_XBUTTONDOWN: case WM_XBUTTONUP:
				m_pInput->SetMouseXButton(wParam);
				m_pInput->MouseIn(lParam);
				return 0;
		}
	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}