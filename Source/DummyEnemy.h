#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "Randomiser.h"
#include "GameObject.h"
#include "State.h"

const unsigned int		StartScreenPositionX = 100;
const unsigned int		StartScreenPositionY = 50;

class DummyEnemy : public GameObject
{
public:

	DummyEnemy();
	virtual				~DummyEnemy();

	void				Init(const Vector2& position, HitBoxManager* hitBoxManager, SpriteSheet* sprite, Animator* animator);
	
	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();
	
	bool				GetIsActive() const { return m_active; }

	void				SetEnemyState(State<DummyEnemy>* state);
	void				ReturnToPreviousState();
	State<DummyEnemy>*	GetState() const { return m_currentState; }

private:
	State<DummyEnemy>*	m_currentState;			// player states for state machine
	State<DummyEnemy>*	m_previousState;		// record of previous state for state blips
	State<DummyEnemy>*	m_globalState;			// global state for common player methods
};

#endif _ENEMY_H_