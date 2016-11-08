#include "Input.h"

Input::Input() :
m_mouseX(0),
m_mouseY(0),
m_mouseClicked(false)
{
	// set all keypressed to false
	ClearKeysPressed();
}

Input::~Input()
{
}

void
Input::SetKeyDown(WPARAM wParam)
{
	m_keyPressed[wParam] = true; // set keypressed to true
}

void
Input::SetKeyUp(WPARAM wParam)
{
	m_keyPressed[wParam] = false; // set keypressed to false
}

void
Input::SetMouseIn(LPARAM lParam)
{
	m_mouseX = (short)LOWORD(lParam); // set mouse x position
	m_mouseY = (short)HIWORD(lParam); // set mouse y position
}

void
Input::SetMouseX(UINT x)
{
	m_mouseX = x;
}

void 
Input::SetMouseY(UINT y)
{
	m_mouseY = y;
}

void
Input::SetMouseClicked(bool button)
{
	m_mouseClicked = button; 
}

void 
Input::ClearKeysPressed()
{
	for(size_t i = 0; i < MAX_KEY_ARRAY; i++)
	{
		m_keyPressed[i] = false;
	}
}

bool 
Input::IsKeyDown(UCHAR key) const
{
	return m_keyPressed[key]; // return keypressed state
}
