// DummyEnemyHurtState.h
// Christopher Ball 2019
// enemy state when hurt

#ifndef _DUMMYENEMY_HURT_STATE_
#define _DUMMYENEMY_HURT_STATE_

#include "State.h"

class DummyEnemy;

class DummyEnemyHurtState : public State<DummyEnemy>
{
public:
	// static instance call
	static DummyEnemyHurtState* Instance();

	virtual void OnEnter(DummyEnemy* enemy);
	virtual void Execute(DummyEnemy* enemy);
	virtual void OnExit(DummyEnemy* enemy);

private:
	DummyEnemyHurtState() {}
	DummyEnemyHurtState(const DummyEnemyHurtState&);
	DummyEnemyHurtState operator=(DummyEnemyHurtState const&);
}

#endif // !_DUMMYENEMY_HURT_STATE_