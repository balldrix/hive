#pragma once

#include "pch.h"

class Graphics;
class Input;
class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void							Init(Graphics* graphics, Input* input);		

	void							AddState(GameState* state);					
	void							SwitchState(const wchar_t* stateName);		
	GameState*						GetCurrentState() const;					
	const wchar_t*					GetCurrentStateName() const;				

	void							ProcessInput();								
	void							Update(float deltaTime);					
	void							ProcessCollisions();						
	void							Render();									

	void							ReleaseAll();								

	Graphics*						GetGraphics() const { return m_graphics; }	
	Input*							GetInput() const { return m_input; }		

private:
	GameState*						m_currentState;								
	std::vector<GameState*>			m_stateList;								

	Graphics*						m_graphics;									
	Input*							m_input;									
};
