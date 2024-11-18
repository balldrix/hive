#include "Input.h"

#include "Logger.h"

Input::Input() :
	m_mouseX(0),
	m_mouseY(0),
	m_mouseClicked(false),
	m_gamePad(nullptr)
{
	ClearAll();
}

Input::~Input()
{
	Shutdown();
}

void Input::Init()
{
	Logger::LogInfo("Initialising Inputs.");

	m_gamePad = new GamePad();
}

void Input::UpdateGamePad()
{
	if(!m_gamePad->GetState(0).IsConnected())
	{
		m_buttons.Reset();
		return;
	}

	m_buttons.Update(m_gamePad->GetState(0));
}

void Input::SetKeyDown(WPARAM wParam)
{
	if(wParam < MAX_KEY_ARRAY)
	{
		m_keysPressed[wParam] = true;
		m_keysDown[wParam] = true;
	}
}

void Input::SetKeyUp(WPARAM wParam)
{
	if(wParam < MAX_KEY_ARRAY)
	{
		m_keysDown[wParam] = false;
	}
}

void Input::SetMouseIn(LPARAM lParam)
{
	m_mouseX = (short)LOWORD(lParam);
	m_mouseY = (short)HIWORD(lParam);
}

void Input::SetMouseX(UINT x)
{
	m_mouseX = x;
}

void Input::SetMouseY(UINT y)
{
	m_mouseY = y;
}

void Input::SetMouseClicked(bool button)
{
	m_mouseClicked = button;
}

void Input::ClearKeysDown()
{
	for(size_t i = 0; i < MAX_KEY_ARRAY; i++)
	{
		m_keysDown[i] = false;
	}
}

void Input::ClearKeysPressed()
{
	for(size_t i = 0; i < MAX_KEY_ARRAY; i++)
	{
		m_keysPressed[i] = false;
	}
}

void Input::ClearAll()
{
	ClearKeysPressed();
	ClearKeysDown();
}

bool Input::IsKeyDown(UCHAR key) const
{
	if(key < MAX_KEY_ARRAY)
		return m_keysDown[key];
	else
		return false;
}

bool Input::WasKeyPressed(UCHAR key) const
{
	if(key < MAX_KEY_ARRAY)
		return m_keysPressed[key];
	else
		return false;
}

void Input::Shutdown()
{
	Logger::LogInfo("Shutting down Inputs.");

	delete m_gamePad;
	m_gamePad = nullptr;
}

void Input::Suspend()
{
	m_gamePad->Suspend();
	m_buttons.Reset();
}

void Input::Resume()
{
	m_gamePad->Resume();
	m_buttons.Reset();
}

bool Input::WasGamePadButtonPressed(GamePad::ButtonStateTracker::ButtonState buttonState) const
{
	return buttonState == GamePad::ButtonStateTracker::PRESSED;	
}
