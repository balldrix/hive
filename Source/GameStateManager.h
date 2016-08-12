#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_

#include "Graphics.h"
#include "Input.h"
#include "LinkedList.h"
#include "GameState.h"

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void			CreateGlobalSystems(HWND hWindow, Graphics* graphics, Input* input);

	void			AddState(GameState* state);
	void			SwitchState(const char* stateName);
	GameState*		GetCurrentState() const;
	const char*		GetCurrentStateName() const;
	void			Update(float deltaTime);
	void			Render();
	void			OnLostDevice();
	void			ResetAll();
	void			ReleaseAll();

	Graphics*		GetGraphics() const { return m_pGraphics; }
	Input*			GetInput() const { return m_pInput; }
	HWND			GetHandle() const { return m_hWindow; }


private:
	GameState*				m_currentState;
	LinkedList<GameState*>	m_stateList;

	HWND					m_hWindow;
	Graphics*				m_pGraphics;
	Input*					m_pInput;
};


#endif _GAMESTATEMANAGER_H_
