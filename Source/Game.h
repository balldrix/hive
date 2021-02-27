// Game.h
// Christopher Ball 2019-2021

#pragma once

#include "pch.h"
#include "Timer.h"

class Window;
class Graphics;
class Input;
class GameStateManager;


class Game
{
public:
	Game();
	~Game();
	void				Init(Window* window, Graphics* graphics);

	void				Run();

	void				ProcessInput(); 
	void				Update(float deltaTime);
	void				ProcessCollisions();
	void				Render();

	void				ReleaseAll();
	void				DeleteAll();

	LRESULT				MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	Window*				m_window;
	Graphics*			m_graphics; 
	SpriteBatch*		m_spriteBatch;
	Input*				m_input; 
	GameStateManager*	m_gameStateManager; 
		
	Timer				m_timer;
	float				m_timerFreq;
	float				m_gameTime;
	float				m_currentTime;
	float				m_clientWidth;
	float				m_clientHeight;
	bool				m_paused;
	bool				m_retryAudio;
};
