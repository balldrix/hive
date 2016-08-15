#ifndef _GAME_H_
#define _GAME_H_

#define WIN32_LEAN_AND_MEAN

#include "pch.h"
#include "Graphics.h"
#include "Timer.h"

// forward declarations
class GameStateManager;
class Input;

class Game
{
public:
	Game();
	~Game();
	
	//Initialise the game variables
	void	Init(Graphics* graphics);

	// run method called in winmain message loop
	void	Run();

	void	ReleaseAll();
	void	ResetAll();

	// delete reserved memory
	void	DeleteAll();

	// render game objects
	void	RenderGame();

	// handle lost device
	void	HandleLostDevice();

	// set new display mode
	void			SetDisplayMode(DisplayMode mode);

	// return pointer to Graphics
	Graphics*		GetGraphics()	{ return m_pGraphics; }

	// return pointer to Input
	Input*			GetInput()		{ return m_pInput; }

	// exit game
	void			Exit()			{ PostMessage(m_hWindow, WM_DESTROY, 0, 0); }

	// Pure virtual methods only the derived class can define
	// update game 
	void	Update(float deltaTime);
	
	// render graphics
	void	Render();

	// handle windows messages
	LRESULT			MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	GameStateManager*	m_stateManager;
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