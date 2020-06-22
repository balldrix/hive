#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "pch.h"
#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"
#include "PlayerData.h"

// forward declarations
class ControlSystem;

class Player : public GameObject
{
public:
	Player();
	virtual					~Player();
							
	void					Init(SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);
							
	bool					LoadData(std::string filename);
	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	void					Reset();

	StateMachine<Player>*	GetStateMachine() const { return m_stateMachine; }

	float					GetWalkSpeed() const { return m_playerData.objectData.walkSpeed; }

	// movement
	void					Move(const Vector2 &direction);
	void					Stop();

	// attacks
	void					Attack();
	void					ApplyDamage(GameObject* source, const int& amount);
	void					Knockback(const Vector2& direction, const float& force);

private:
	PlayerData				m_playerData;
	StateMachine<Player>*	m_stateMachine;
};

#endif _PLAYER_H_