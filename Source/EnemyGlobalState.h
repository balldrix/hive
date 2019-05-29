// EnemyGlobalState.h
// Christopher Ball 2019
// global state for common enemy methods

#ifndef _ENEMY_GLOBAL_STATE_
#define	_ENEMY_GLOBAL_STATE_

#include "State.h"

class Enemy;

class EnemyGlobalState : public State<Enemy>
{
public:
	// static instance call
	static EnemyGlobalState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyGlobalState() {}
	EnemyGlobalState(const EnemyGlobalState&);
	EnemyGlobalState operator=(EnemyGlobalState const&);
};
#endif // !_ENEMY_GLOBAL_STATE_
