#ifndef _DUMMY_H_
#define _DUMMY_H_

#include "Constants.h"
#include "GameObject.h"
#include "State.h"
#include "StateMachine.h"

const unsigned int		DummyStartScreenPositionX = 65;
const unsigned int		DummyStartScreenPositionY = 70;

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

#endif _DUMMY_H_