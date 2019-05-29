// Enemy.h
// Christopher Ball 2019
// Enemy class 

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "Randomiser.h"
#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"

const unsigned int		EnemyStartScreenPositionX = 40;
const unsigned int		EnemyStartScreenPositionY = 70;

class Enemy : public GameObject
{
public:

	Enemy();
	virtual				~Enemy();

	void				Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager);

	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();

	StateMachine<Enemy>* GetStateMachine() const { return m_stateMachine; }

	void				ApplyDamage(GameObject* source, const int& amount);
	void				Knockback(const Vector2& direction, const float& force);

private:
	StateMachine<Enemy>* m_stateMachine;
};

#endif _ENEMY_H_