#ifndef _INPUT_H_
#define _INPUT_H_

#define WIN32_MEAN_AND_LEAN

class Input;

#include <Windows.h>
#include <windowsx.h>
#include <string>
#include <Xinput.h>
#include "Controls.h"

const unsigned int		MAX_CONTROLLERS = 4;
const DWORD				GAMEPAD_THUMBSTICK_DEADZONE = (DWORD)(0.20f * 0x7FFF); // 0x7FFF = 32767 (max value of thumbstick)
const DWORD				GAMEPAD_TRIGGER_DEADZONE = 30;

using namespace std;

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

struct ControllerState
{
	XINPUT_STATE		state;
	XINPUT_VIBRATION	vibration;
	float				vibrateTimeLeft;
	float				vibrateTimeRight;
	bool				connected;
};


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
	string				GetTextIn() const { return m_textIn; }

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
	void				SetMouseLButton(bool button) { m_mouseLButton = button; }

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

	// check for controllers
	void				CheckControllers();

	// read controller data
	void				ReadControllers();

	// return state of controller
	const ControllerState*	GetControllerState(UINT n);

	// return state of controller n's buttons
	const WORD			GetGamepadButtons(UINT n);

	// return state of controller n buttons
	bool				GetGamepadDpadUp(UINT n);
	bool				GetGamepadDpadDown(UINT n);
	bool				GetGamepadDpadLeft(UINT n);
	bool				GetGamepadDpadRight(UINT n);
	bool				GetGamepadStart(UINT n);
	bool				GetGamepadBack(UINT n);
	bool				GetGamepadLeftThumb(UINT n);
	bool				GetGamepadRightThumb(UINT n);
	bool				GetGamepadLeftShoulder(UINT n);
	bool				GetGamepadRightShoulder(UINT n);
	bool				GetGamepadA(UINT n);
	bool				GetGamepadB(UINT n);
	bool				GetGamepadX(UINT n);
	bool				GetGamepadY(UINT n);

	// return state of gamepad triggers
	BYTE				GetGamepadLeftTrigger(UINT n);
	BYTE				GetGamepadRightTrigger(UINT n);

	// return state of gamepad thumb sticks
	SHORT				GetGamepadThumbLX(UINT n);
	SHORT				GetGamepadThumbLY(UINT n);
	SHORT				GetGamepadThumbRX(UINT n);
	SHORT				GetGamepadThumbRY(UINT n);

	// vibrate controllers
	void				GamepadVibrateLeft(UINT n, WORD speed, float sec);
	void				GamepadVibrateRight(UINT n, WORD speed, float sec);

	void				VibrateControllers(float deltaTime);


	// clear all input data
	void				ClearAll() { Clear(inputNS::KEYS_MOUSE_TEXT); }
	
	// clear input data
	void				Clear(UCHAR data);

private:	
	bool				m_keysDown[inputNS::KEYS_ARRAY_LEN];
	bool				m_keysPressed[inputNS::KEYS_ARRAY_LEN];

	string				m_textIn;
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

	ControllerState		m_controllers[MAX_CONTROLLERS];
};

#endif  _INPUT_H_

