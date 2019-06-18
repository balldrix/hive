// Input.h
// Christopher Ball 2019
// Manages keyboard and mouse input
// technique learnt from Charles Kelly - Programming 2D Games

#ifndef _INPUT_H_
#define _INPUT_H_

#include "pch.h"

/* ****************************
Keys
*******************************/

const UCHAR CONSOLE_KEY = VK_OEM_3;
const UCHAR ESC_KEY = VK_ESCAPE;
const UCHAR	ALT_KEY = VK_MENU;
const UCHAR ENTER_KEY = VK_RETURN;
const UCHAR F4_KEY = VK_F4;
const UCHAR F5_KEY = VK_F5;

// rename consts 
const UCHAR PLAYER_UP_KEY = VK_UP;
const UCHAR PLAYER_DOWN_KEY = VK_DOWN;
const UCHAR PLAYER_LEFT_KEY = VK_LEFT;
const UCHAR PLAYER_RIGHT_KEY = VK_RIGHT;
const UCHAR PLAYER_A_KEY = 0x58; // x key
const UCHAR PLAYER_B_KEY = 0x5A; // z key


 /* ****************************
 XboX Controller
 *******************************/

const DWORD GAMEPAD_DPAD_UP = 0x0001;
const DWORD GAMEPAD_DPAD_DOWN = 0x0002;
const DWORD GAMEPAD_DPAD_LEFT = 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT = 0x0008;
const DWORD GAMEPAD_START_BUTTON = 0x0010;
const DWORD GAMEPAD_BACK_BUTTON = 0x0020;
const DWORD GAMEPAD_LEFT_THUMB = 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB = 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER = 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER = 0x0200;
const DWORD GAMEPAD_A = 0x1000;
const DWORD GAMEPAD_B = 0x2000;
const DWORD GAMEPAD_X = 0x4000;
const DWORD GAMEPAD_Y = 0x8000;

const UINT MAX_KEY_ARRAY = 256;		// max number of keys available
const float MAX_INPUT_DELAY = 0.2f;	// time delay between inputs

class Input
{
public:
	Input();
	~Input();

	void SetKeyDown(WPARAM wParam); // set key down 
	void SetKeyUp(WPARAM wParam);	// set key up
	void SetMouseIn(LPARAM lParam); // set mouse position
	void SetMouseX(UINT x);			// set mouse x position
	void SetMouseY(UINT y);			// set mouse y position

	void SetMouseClicked(bool button); // set Mouse Left Button status

	void ClearKeysDown();		// clear keys pressed array
	void ClearKeysPressed();		// clear keys pressed array
	void ClearAll();			// clear all input

	bool IsKeyDown(UCHAR key) const;			// check if key pressed
	bool WasKeyPressed(UCHAR key) const;	// check if key was pressed
	UINT GetMouseX() const { return m_mouseX; } // return mouse X position
	UINT GetMouseY() const { return m_mouseY; } // return mouse Y position
	bool GetMouseClicked() const { return m_mouseClicked; } // return mouse clicked status


private:
	bool m_keysPressed[MAX_KEY_ARRAY]; // boolean array of keys 
	bool m_keysDown[MAX_KEY_ARRAY]; // boolean array of keys 
	UINT m_mouseX;					// mouse x position
	UINT m_mouseY;					// mouse y position
	bool m_mouseClicked;			// L mouse button
};

#endif _INPUT_H_
