// DummyEnemyDeadState.h
// Christopher Ball 2019
// enemy state when dead

#ifndef _DUMMYENEMY_DEAD_STATE_
#define _DUMMYENEMY_DEAD_STATE_

#include "State.h"

class DummyEnemy;

class DummyEnemyDeadState : public State<DummyEnemy>
{
public:
	// static instance call
	static DummyEnemyDeadState* Instance();

	virtual void OnEnter(DummyEnemy* enemy);
	virtual void Execute(DummyEnemy* enemy);
	virtual void OnExit(DummyEnemy* enemy);

private:
	DummyEnemyDeadState() {}
	DummyEnemyDeadState(const DummyEnemyDeadState&);
	DummyEnemyDeadState operator=(DummyEnemyDeadState const&);
}

#endif // !_DUMMYENEMY_DEAD_STATE_