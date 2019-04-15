// DummyEnemyIdleState.h
// Christopher Ball 2019
// enemy state when Idle

#ifndef _DUMMYENEMY_IDLE_STATE_
#define	_DUMMYENEMY_IDLE_STATE_

#include "State.h"

// forward declaration
class DummyEnemy;

class DummyEnemyIdleState : public State<DummyEnemy>
{
public:
	// static instance call
	static DummyEnemyIdleState* Instance();

	virtual void OnEnter(DummyEnemy* enemy);
	virtual void Execute(DummyEnemy* enemy);
	virtual void OnExit(DummyEnemy* enemy);

private:
	DummyEnemyIdleState() {}
	DummyEnemyIdleState(const DummyEnemyIdleState&);
	DummyEnemyIdleState operator=(DummyEnemyIdleState const&);
};

#endif // !_DUMMYENEMY_IDLE_STATE_