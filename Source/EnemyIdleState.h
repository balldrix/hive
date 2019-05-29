// EnemyIdleState.h
// Christopher Ball 2019
// manages state when enemy is idle

#ifndef _ENEMY_IDLE_STATE_
#define	_ENEMY_IDLE_STATE_

#include "State.h"

// forward declaration
class Enemy;

class EnemyIdleState : public State<Enemy>
{
public:
	// static instance call
	static EnemyIdleState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyIdleState();
	EnemyIdleState(std::string name);
	EnemyIdleState(const EnemyIdleState&);
	EnemyIdleState operator=(EnemyIdleState const&);
};

#endif // !_ENEMY_IDLE_STATE_

