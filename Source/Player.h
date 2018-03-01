#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"
#include "State.h"

// forward declarations
class ControlSystem;
class Sprite;

// player constants TODO move into struct with data in txt file
const float				StartScreenPositionX = 30;
const float				StartScreenPositionY = 70;
const unsigned int		WalkSpeed = 40;
const float				PlayerAcceleration = 1.0f;
const float				PlayerDeceleration = 3.0f;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void				Init(Sprite* sprite, Vector2 position);
	void				AddControlSystem(ControlSystem* controlSystem);

	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();

	void				SetPlayerState(State<Player>* state);
	State<Player>*		GetState() const { return m_currentState; }
	ControlSystem*		GetControlSystem() const { return m_controlSystem; }
private:
	ControlSystem*		m_controlSystem;		// pointer to control system
	Sprite*				m_sprite;				// player sprite sheet
	State<Player>*		m_currentState;			// player states for state machine
};

#endif _PLAYER_H_