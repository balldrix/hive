#pragma once

class GameState
{
public:
	GameState();
	GameState(const wchar_t* stateName);
	virtual ~GameState(void) {};

	virtual void	OnEntry() {};				//  load all assetts when entering state
	virtual void	OnExit() {};				// delete all assetts when changing state

	virtual void	ProcessInput() {};			// process keyboard and mouse input
	virtual void	Update(float deltaTime) {}; // update game state
	virtual void	ProcessCollisions() {};		// check for collisions
	virtual void	Render() {};				// render game state

	virtual void	ReleaseAll() {};			// release all resources in state

	virtual const wchar_t*	GetStateName() const; // return name of current state

protected:
	const wchar_t*	m_stateName; 				// name of game state
	float			m_inputTimer; 				// var used to create input delay
	bool			m_inputReady; 				// has a key been pressed already?
};