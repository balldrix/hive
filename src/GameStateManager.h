#pragma once

#include <string>
#include <vector>

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
	void							SwitchState(std::string stateName);		
	
	GameState*						GetState(std::string stateName) const;
	GameState*						GetCurrentState() const;					
	std::string						GetCurrentStateName() const;				

	void							ProcessInput();								
	void							Update(float deltaTime);					
	void							ProcessCollisions();						
	void							Render();									

	Graphics*						GetGraphics() const { return m_graphics; }	
	Input*							GetInput() const { return m_input; }	

private:
	GameState*						m_currentState;								
	std::vector<GameState*>			m_stateList;								

	Graphics*						m_graphics;									
	Input*							m_input;									
};