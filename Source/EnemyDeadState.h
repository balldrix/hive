// EnemyDeadState.h
// Christopher Ball 2019
// manages state when enemy is dead

#ifndef _ENEMY_DEAD_STATE_
#define	_ENEMY_DEAD_STATE_

#include "State.h"

// forward declaration
class Enemy;

class EnemyDeadState : public State<Enemy>
{
public:
	// static instance call
	static EnemyDeadState* Instance();

	virtual void OnEnter(Enemy* enemy);
	bool EnemyIsDead(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyDeadState() {}
	~EnemyDeadState() {}
	EnemyDeadState(std::string name);
	EnemyDeadState(const EnemyDeadState&);
	EnemyDeadState& operator=(const EnemyDeadState&);
};

#endif // !_ENEMY_DEAD_STATE_

