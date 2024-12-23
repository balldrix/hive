#pragma once

#include <directxtk/GamePad.h>
#include <windows.h>

using namespace DirectX;

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
const UCHAR PLAYER_X_KEY = 0x58; // x key
const UCHAR PLAYER_Z_KEY = 0x5A; // z key
const UCHAR PLAYER_C_KEY = 0x43; // c key
const UCHAR PLAYER_V_KEY = 0x56; // v keys

const UINT MAX_KEY_ARRAY = 256;	
const float MAX_INPUT_DELAY = 0.2f;

class Input
{
public:
	Input();
	~Input();

	void Init();

	void UpdateGamePad();
	void SetKeyDown(WPARAM wParam); 
	void SetKeyUp(WPARAM wParam);
	void SetMouseIn(LPARAM lParam);
	void SetMouseX(UINT x);
	void SetMouseY(UINT y);	

	void SetMouseClicked(bool button);

	void ClearKeysDown();
	void ClearKeysPressed();
	void ClearAll();

	bool IsKeyDown(UCHAR key) const;	
	bool WasKeyPressed(UCHAR key) const;
	UINT GetMouseX() const { return m_mouseX; }
	UINT GetMouseY() const { return m_mouseY; } 
	bool GetMouseClicked() const { return m_mouseClicked; } 

	void Shutdown();

	void Suspend();
	void Resume();

	bool WasGamePadButtonPressed(GamePad::ButtonStateTracker::ButtonState buttonState) const;
	GamePad::State GetGamePadState() const { return m_gamePad->GetState(0); }
	GamePad::ButtonStateTracker GetGamePadButtons() const { return m_buttons; }

private:
	bool m_keysPressed[MAX_KEY_ARRAY];
	bool m_keysDown[MAX_KEY_ARRAY]; 
	UINT m_mouseX;					
	UINT m_mouseY;					
	bool m_mouseClicked;			
	GamePad* m_gamePad;
	GamePad::ButtonStateTracker m_buttons;
};
