#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "Randomiser.h"
#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"

const unsigned int		DummyStartScreenPositionX = 120;
const unsigned int		DummyStartScreenPositionY = 80;

class Dummy : public GameObject
{
public:

	Dummy();
	virtual				~Dummy();

	void				Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager);
	
	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();
	
	StateMachine<Dummy>* GetStateMachine() const { return m_stateMachine; }

	void				ApplyDamage(GameObject* source, const int& amount);
	void				Knockback(const Vector2& direction, const float& force);

private:
	StateMachine<Dummy>* m_stateMachine;
};

#endif _ENEMY_H_