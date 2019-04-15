#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "Randomiser.h"
#include "GameObject.h"
#include "State.h"

const unsigned int		DummyStartScreenPositionX = 100;
const unsigned int		DummyStartScreenPositionY = 50;

class Dummy : public GameObject
{
public:

	Dummy();
	virtual				~Dummy();

	void				Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager);
	
	void				Update(float deltaTime);
	void				Render(Graphics* graphics);
	void				Reset();
	
	bool				GetIsActive() const { return m_active; }

	void				SetEnemyState(State<Dummy>* state);
	void				ReturnToPreviousState();
	State<Dummy>*	GetState() const { return m_currentState; }

private:
	State<Dummy>*	m_currentState;			// player states for state machine
	State<Dummy>*	m_previousState;		// record of previous state for state blips
	State<Dummy>*	m_globalState;			// global state for common player methods
};

#endif _ENEMY_H_