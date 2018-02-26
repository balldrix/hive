// Input.h
// Christopher Ball 2017
// Manages keyboard and mouse input
// technique learnt from Charles Kelly - Programming 2D Games

#ifndef _INPUT_H_
#define _INPUT_H_

#include "pch.h"

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
