// EnemyHurtState.h
// Christopher Ball 2019
// manages state when enemy is hurt

#ifndef _ENEMY_HURT_STATE_
#define	_ENEMY_HURT_STATE_

#include "State.h"

// forward declaration
class Enemy;

class EnemyHurtState : public State<Enemy>
{
public:
	// static instance call
	static EnemyHurtState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyHurtState() {}
	~EnemyHurtState() {}
	EnemyHurtState(std::string name);
	EnemyHurtState(const EnemyHurtState&);
	EnemyHurtState& operator=(const EnemyHurtState&);
};

#endif // !_ENEMY_HURT_STATE_

