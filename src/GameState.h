#pragma once

#include <string>

class GameStateManager;

class GameState
{
public:
	GameState();
	GameState(std::string stateName);
	virtual ~GameState(void) {};

	virtual void	OnEntry() {};
	virtual void	OnExit() {};

	virtual void	LoadAssets() {};
	virtual void	DeleteAssets() {};
	virtual void	ProcessInput() {};
	virtual void	Update(float deltaTime) {};
	virtual void	ProcessCollisions() {};
	virtual void	Render() {};

	virtual std::string	GetStateName() const;

protected:
	GameStateManager* m_gameStateManager;

	std::string	m_stateName;
	float m_inputTimer; 
	bool m_inputReady; 
};