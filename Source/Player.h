#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"

// forward declarations
class ControlSystem;

// player constants 
// TODO move into struct with data in txt file
const unsigned int		PlayerStartScreenPositionX = 20;
const unsigned int		PlayerStartScreenPositionY = 60;
const unsigned int		WalkSpeed = 30;
const float				PlayerAcceleration = 1.0f;
const float				PlayerDeceleration = 4.0f;

class Player : public GameObject
{
public:
	Player();
	virtual					~Player();
							
	void					Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);
							
	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	void					Reset();

	StateMachine<Player>*	GetStateMachine() const { return m_stateMachine; }

	// movement
	void					Move(const Vector2 &direction);
	void					Stop();

	// attacks
	void					Attack();

private:
	StateMachine<Player>*	m_stateMachine;
};

#endif _PLAYER_H_