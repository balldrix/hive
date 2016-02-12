#include "Game.h"
#include "Constants.h"

Game::Game() :
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
	DeleteAll();
	ShowCursor(true);
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
			m_pInput->SetMouseLButton(true);
			m_pInput->MouseIn(lParam);
			return 0;
		case WM_LBUTTONUP:
			m_pInput->SetMouseLButton(false);
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
		case WM_DEVICECHANGE:
			m_pInput->CheckControllers();
			return 0;
		}
	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

void
Game::Init(HWND hWindow)
{
	// set windows handle
	m_hWindow = hWindow;

	m_pGraphics = new Graphics();
	m_pInput = new Input();

	// initialise graphics object
	m_pGraphics->Init(m_hWindow, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);

	// initialise input 
	m_pInput->Init(m_hWindow, false);

	// set timer frequency
	m_timeFreq = m_pTimer.GetFrequency();

	// set timer start
	m_timeStart = m_pTimer.GetTicks();

	m_initialised = true;

	// seed the randoms with the current time
	srand((int)time(NULL));
}

// run method called in winmain message loop
void
Game::Run(HWND hWindow)
{
	if (m_pGraphics != NULL)
	{
		m_timeEnd = m_pTimer.GetTicks();

		m_deltaTime = ((float)(m_timeEnd - m_timeStart) / (float)m_timeFreq);

		if (m_deltaTime < MIN_FRAME_TIME)
		{
			m_sleepTime = (DWORD)((MIN_FRAME_TIME - m_deltaTime) * 1000);
			timeBeginPeriod(1);
			Sleep(m_sleepTime);
			timeEndPeriod(1);
			return;
		}

		if (m_deltaTime > 0.0)
		{
			m_fps = (m_fps * 0.99f) + (0.01f / m_deltaTime);
		}

		if (m_deltaTime > MAX_FRAME_TIME)
		{
			m_deltaTime = MAX_FRAME_TIME;
		}

		m_timeStart = m_timeEnd;

		m_pInput->ReadControllers();

		// if Alt+Enter toggle fullscreen/window
		if (m_pInput->IsKeyDown(ALT_KEY) && m_pInput->WasKeyPressed(ENTER_KEY))
		{
			SetDisplayMode(graphicsNS::TOGGLE); // toggle fullscreen/window
		}

		if (m_pInput->IsKeyDown(ESC_KEY))
		{
			Exit();
		}

		Update(m_deltaTime);	
		m_pInput->VibrateControllers(m_deltaTime);

		RenderGame();
		
		m_pInput->Clear(inputNS::KEYS_PRESSED);
	}
}

// delete reserved memory
void
Game::DeleteAll()
{	
	ReleaseAll();

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

	m_initialised = false;
}

// render game objects
void
Game::RenderGame()
{
	m_result = m_pGraphics->Begin();

	if (m_result == S_OK)
	{
		Render();
		m_pGraphics->End();
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
Game::SetDisplayMode(graphicsNS::DISPLAY_MODE mode)
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