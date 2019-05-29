// EnemyRunningState.h
// Christopher Ball 2019
// manages state when enemy is running

#ifndef _ENEMY_RUNNING_STATE_
#define	_ENEMY_RUNNING_STATE_

#include "State.h"

// forward declaration
class Enemy;

class EnemyRunningState : public State<Enemy>
{
public:
	// static instance call
	static EnemyRunningState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyRunningState();
	EnemyRunningState(std::string name);
	EnemyRunningState(const EnemyRunningState&);
	EnemyRunningState operator=(EnemyRunningState const&);
};

#endif // !_ENEMY_RUNNING_STATE_