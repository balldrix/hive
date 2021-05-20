#pragma once

class GameState
{
public:
	GameState();
	GameState(const wchar_t* stateName);
	virtual ~GameState(void) {};

	virtual void	OnEntry() {};				
	virtual void	OnExit() {};				

	virtual void	ProcessInput() {};			
	virtual void	Update(float deltaTime) {}; 
	virtual void	ProcessCollisions() {};		
	virtual void	Render() {};				

	virtual void	ReleaseAll() {};			

	virtual const wchar_t*	GetStateName() const; 

protected:
	const wchar_t*	m_stateName; 
	float			m_inputTimer; 
	bool			m_inputReady; 
};