#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"
#include "State.h"

// forward declarations
class ControlSystem;
class SpriteSheet;
class Animator;

// player constants TODO move into struct with data in txt file
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

	void				Init(ControlSystem* controlSystem, SpriteSheet* sprite, Vector2 position);
	void				Init(ControlSystem* controlSystem, SpriteSheet* sprite, Animator* animator, Vector2 position);

	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();

	// TODO create state machine
	void				SetPlayerState(State<Player>* state);
	void				ReturnToPreviousState();

	State<Player>*		GetState() const { return m_currentState; }
	ControlSystem*		GetControlSystem() const { return m_controlSystem; }
	SpriteSheet*		GetSprite() const { return m_sprite; }
	Animator*			GetAnimator() const { return m_animator; }

private:
	ControlSystem*		m_controlSystem;		// pointer to control system

	SpriteSheet*		m_sprite;				// player sprite sheet
	Animator*			m_animator;				// player animation controller
	
	State<Player>*		m_currentState;			// player states for state machine
	State<Player>*		m_previousState;		// record of previous state for state blips
	State<Player>*		m_globalState;			// global state for common player methods
};

#endif _PLAYER_H_