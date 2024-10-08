#pragma once

#include <string>

class GameState
{
public:
	GameState();
	GameState(std::string stateName);
	virtual ~GameState(void) {};

	virtual void	OnEntry() {};				
	virtual void	OnExit() {};				

	virtual void	ProcessInput() {};			
	virtual void	Update(float deltaTime) {}; 
	virtual void	ProcessCollisions() {};		
	virtual void	Render() {};				

	virtual void	ReleaseAll() {};			

	virtual std::string	GetStateName() const;

protected:
	std::string	m_stateName;
	float			m_inputTimer; 
	bool			m_inputReady; 
};