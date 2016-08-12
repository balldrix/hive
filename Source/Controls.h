#ifndef _CONTROLS_H_
#define _CONTROLS_H_

#include <Windows.h>


/* ****************************
	Keys
*******************************/

const UCHAR CONSOLE_KEY				= VK_OEM_3;
const UCHAR ESC_KEY					= VK_ESCAPE;
const UCHAR	ALT_KEY					= VK_MENU;
const UCHAR ENTER_KEY				= VK_RETURN;
const UCHAR F4_KEY					= VK_F4;
const UCHAR F5_KEY					= VK_F5;
		
const UCHAR PLAYER_UP_KEY			= VK_UP;
const UCHAR PLAYER_DOWN_KEY			= VK_DOWN;
const UCHAR PLAYER_LEFT_KEY			= VK_LEFT;
const UCHAR PLAYER_RIGHT_KEY		= VK_RIGHT;
const UCHAR PLAYER_A_KEY			= 0x58; // x key
const UCHAR PLAYER_B_KEY			= 0x5A; // z key


/* ****************************
	XboX Controller
*******************************/

const DWORD GAMEPAD_DPAD_UP			= 0x0001;
const DWORD GAMEPAD_DPAD_DOWN		= 0x0002;
const DWORD GAMEPAD_DPAD_LEFT		= 0x0004;
const DWORD GAMEPAD_DPAD_RIGHT		= 0x0008;
const DWORD GAMEPAD_START_BUTTON	= 0x0010;
const DWORD GAMEPAD_BACK_BUTTON		= 0x0020;
const DWORD GAMEPAD_LEFT_THUMB		= 0x0040;
const DWORD GAMEPAD_RIGHT_THUMB		= 0x0080;
const DWORD GAMEPAD_LEFT_SHOULDER	= 0x0100;
const DWORD GAMEPAD_RIGHT_SHOULDER	= 0x0200;
const DWORD GAMEPAD_A				= 0x1000;
const DWORD GAMEPAD_B				= 0x2000;
const DWORD GAMEPAD_X				= 0x4000;
const DWORD GAMEPAD_Y				= 0x8000;

#endif _CONTROLS_H_