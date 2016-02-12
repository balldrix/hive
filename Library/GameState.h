#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class GameState
{
public:
	GameState();
	GameState(const char* stateName);
	virtual ~GameState(void) {};

	//  load all assetts when entering state
	virtual void	OnEntry(){};

	// delete all assetts when changing state
	virtual void	OnExit(){};

	virtual void	CheckInput(float deltaTime){};
	virtual void	Update(float deltaTime){};
	virtual void	Render(){};
	virtual void	OnLostDevice(){};
	virtual void	ResetAll() {};
	virtual void	ReleaseAll() {};

	// return name of current state
	const char*		GetStateName() const;

protected:

	// name of game state
	const char*		m_stateName;

	// var used to create input delay
	float			m_inputTimer;

	// has a key been pressed already?
	bool			m_keyPressed;
};

#endif _GAMESTATE_H_