#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"
#include "State.h"

// forward declarations
class ControlSystem;

// player constants 
// TODO move into struct with data in txt file
const unsigned int		StartScreenPositionX = 100;
const unsigned int		StartScreenPositionY = 50;
const unsigned int		WalkSpeed = 30;
const float				PlayerAcceleration = 1.0f;
const float				PlayerDeceleration = 4.0f;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void				Init(ControlSystem* controlSystem, SpriteSheet* sprite, Animator* animator, const Vector2& position, HitBoxManager* hitBoxManager);

	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();

	// TODO create state machine
	void				SetPlayerState(State<Player>* state);
	void				ReturnToPreviousState();

	State<Player>*		GetState() const { return m_currentState; }

	// flip sprite and hitboxes
	void				FlipHorizontally(bool flip);

private:
	State<Player>*		m_currentState;			// player states for state machine
	State<Player>*		m_previousState;		// record of previous state for state blips
	State<Player>*		m_globalState;			// global state for common player methods
};

#endif _PLAYER_H_