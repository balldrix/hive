#ifndef _INPUT_H_
#define _INPUT_H_

#define WIN32_MEAN_AND_LEAN

class Input;

#include "pch.h"
#include "Controls.h"

const float				KEY_DELAY		= 5.0f;

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

namespace inputNS
{
	const int			KEYS_ARRAY_LEN	= 256;

	const UCHAR			KEYS_DOWN		= 1;
	const UCHAR			KEYS_PRESSED	= 2;
	const UCHAR			MOUSE			= 4;
	const UCHAR			TEXT_IN			= 8;
	const UCHAR			KEYS_MOUSE_TEXT = KEYS_DOWN + KEYS_PRESSED + MOUSE + TEXT_IN;
}

class Input
{
public:
	Input();
	~Input();

	// initialise inputs
	void				Init(HWND hWindow, bool capture);

	/* **********************************************
		KEYS INPUT
	********************************************** */

	// process KeyDown message
	void				KeyDown(WPARAM wParam);

	// proces KeyUp message
	void				KeyUp(WPARAM wParam);

	// process KeyIn message
	void				KeyIn(WPARAM wParam);

	// return true if virtual key is down
	bool				IsKeyDown(UCHAR vk) const;

	// return true if virtual key was pressed in most recent frame
	bool				WasKeyPressed(UCHAR vk) const;

	// return true if any key was pressed
	bool				AnyKeyPressed() const;

	// return string text
	std::string				GetTextIn() const { return m_textIn; }

	// return last character pressed
	char				GetCharIn() const { return m_charIn; }
	
	// clear specific key pressed
	void				ClearKeyPress(UCHAR vk);

	// clear textIn buffer
	void				ClearTextIn() { m_textIn.clear(); }

	/* **********************************************
		MOUSE INPUT
	********************************************** */
	// process mouse data
	void				MouseIn(LPARAM lParam);

	// process raw mouse data
	void				MouseRawIn(LPARAM lParam);

	// set Mouse Left Button status
	void				SetMouseClicked(bool button) { m_mouseLButton = button; }

	// set Mouse Right Button status
	void				SetMouseRButton(bool button) { m_mouseRButton = button; }

	// set Mouse Middle Button status
	void				SetMouseMButton(bool button) { m_mouseMButton = button; }

	// set Mouse X Button status
	void				SetMouseXButton(WPARAM wParam);

	// return Mouse x position
	int					GetMouseX()	const { return m_mouseX; }

	// return mouse y position
	int					GetMouseY() const { return m_mouseY; }

	// return raw mouse x movement
	int					GetMouseRawX() const { return m_mouseRawX; }

	// return raw mouse y movement
	int					GetMouseRawY() const { return m_mouseRawY; }

	// clear all input data
	void				ClearAll() { Clear(inputNS::KEYS_MOUSE_TEXT); }
	
	// clear input data
	void				Clear(UCHAR data);

private:	
	bool				m_keysDown[inputNS::KEYS_ARRAY_LEN];
	bool				m_keysPressed[inputNS::KEYS_ARRAY_LEN];

	std::string			m_textIn;
	char				m_charIn;
	bool				m_newLine;

	int					m_mouseX;
	int					m_mouseY;
	int					m_mouseRawX;
	int					m_mouseRawY;

	RAWINPUTDEVICE		m_rid[1];

	bool				m_mouseCaptured;
	bool				m_mouseLButton;
	bool				m_mouseRButton;
	bool				m_mouseMButton;
	bool				m_mouseX1Button;
	bool				m_mouseX2Button;
};

#endif  _INPUT_H_

