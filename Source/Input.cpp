#include "Input.h"

Input::Input() :
	m_mouseX(0),
	m_mouseY(0),
	m_mouseClicked(false)
{
	// clear all keys
	ClearAll();
}

Input::~Input()
{
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
	return m_keysDown[key];
}

bool Input::WasKeyPressed(UCHAR key) const
{
	if(key < MAX_KEY_ARRAY)
	{
		return m_keysPressed[key];
	}
	else
	{
		return false;
	}
}
