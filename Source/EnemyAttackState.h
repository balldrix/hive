// EnemyAttackState.h
// Christopher Ball 2019
// manages state when enemy is attacking

#ifndef _ENEMY_ATTACK_STATE_
#define	_ENEMY_ATTACK_STATE_

#include "State.h"

// forward declaration
class Enemy;

class EnemyAttackState : public State<Enemy>
{
public:
	// static instance call
	static EnemyAttackState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyAttackState();
	EnemyAttackState(std::string name);
	EnemyAttackState(const EnemyAttackState&);
	EnemyAttackState operator=(EnemyAttackState const&);
};

#endif // !_ENEMY_ATTACK_STATE_

