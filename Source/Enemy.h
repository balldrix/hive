// Enemy.h
// Christopher Ball 2019
// Enemy class 

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"

const unsigned int			EnemyStartScreenPositionX = 80;
const unsigned int			EnemyStartScreenPositionY = 70;
const unsigned int			EnemyWalkSpeed = 25;
const unsigned int			EnemyRunningSpeed = 40;
const float					EnemyAcceleration = 0.8f;
const float					EnemyDeceleration = 4.5f;
const float					ThinkingTime = 3.5f;

class Player;

class Enemy : public GameObject
{
public:
	Enemy();
	virtual					~Enemy();

	void					Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager);

	void					Update(float deltaTime);
	void					Render(Graphics* graphics);
	void					Reset();

	void					SetPlayerTarget(Player* player);

	Player*					GetPlayerTarget() const { return m_playerTarget; }
	StateMachine<Enemy>*	GetStateMachine() const { return m_stateMachine; }

	void					ApplyDamage(GameObject* source, const int& amount);
	void					Knockback(const Vector2& direction, const float& force);

	float					GetTimer() const { return m_thinkingTimer; }

private:
	Player*					m_playerTarget;
	StateMachine<Enemy>*	m_stateMachine;
	float					m_thinkingTimer;
};

#endif _ENEMY_H_