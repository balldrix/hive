#ifndef _GAME_H_
#define _GAME_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <time.h>
#include "Graphics.h"
#include "Input.h"
#include "Timer.h"
#include "Sprite.h"
#include "GameStateManager.h"

class Game
{
public:
	Game();
	virtual	~Game();
	
	// handle windows messages
	LRESULT			MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

	//Initialise the game variables
	virtual void	Init(HWND hWindow);

	// run method called in winmain message loop
	virtual void	Run(HWND hWindow);

	virtual void	ReleaseAll();
	virtual void	ResetAll();

	// delete reserved memory
	virtual void	DeleteAll();

	// render game objects
	virtual void	RenderGame();

	// handle lost device
	virtual void	HandleLostDevice();

	// set new display mode
	void			SetDisplayMode(graphicsNS::DISPLAY_MODE mode);

	// return pointer to Graphics
	Graphics*		GetGraphics()	{ return m_pGraphics; }

	// return pointer to Input
	Input*			GetInput()		{ return m_pInput; }

	// exit game
	void			Exit()			{ PostMessage(m_hWindow, WM_DESTROY, 0, 0); }

	// Pure virtual methods only the derived class can define
	// update game 
	virtual void	Update(float deltaTime) = 0;
	
	// render graphics
	virtual void	Render() = 0;

protected:

	Graphics*		m_pGraphics;
	Input*			m_pInput;
	Timer			m_pTimer;
	HWND			m_hWindow;
	HRESULT			m_result;
	UINT64			m_timeStart;
	UINT64			m_timeEnd;
	UINT64			m_timeFreq;
	float			m_deltaTime;
	float			m_fps;
	DWORD			m_sleepTime;
	
	bool			m_initialised;
};

#endif  _GAME_H_