// Game.h
// Christopher Ball 2019
// The game class manages the main game loop
// and interacting with game state manager to 
// call update and render the correct state

#ifndef _GAME_H_
#define _GAME_H_

#include "pch.h"
#include "Graphics.h"
#include "Timer.h"

// forward declarations
class Input;
class GameStateManager;

class Game
{
public:
	Game();
	~Game();
	void				Init(Graphics* graphics);	// initialises game class and passes pointer to the graphics class

	void				Run(); // main game function

	void				ProcessInput(); // read inputs
	void				Update(float deltaTime); // update all objects in the scene
	void				AI();
	void				ProcessCollisions();
	void				Render(); // Render scene

	void				SetDisplayMode(DisplayMode mode);

	void				ReleaseAll(); // release all pointers
	void				DeleteAll(); // delete all pointers

	LRESULT				MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam); // deals with windows messages

private:
	Graphics*			m_graphics; // pointer to graphics class for access to the gpu device
	SpriteBatch*		m_spriteBatch; // 2d sprites engine
	Input*				m_input; // manages key and mouse inputs
	GameStateManager*	m_gameStateManager; // manager to switch and call current game state for render/update calls
		
	Timer				m_timer; // helper object for time step
	float				m_timerFreq; // timer frequency 
	float				m_gameTime;	// game timer
	float				m_currentTime; // tick time

	bool				m_retryAudio; // sets if audio device is lost
};

#endif _GAME_H_
