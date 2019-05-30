// EnemyWalkingState.h
// Christopher Ball 2019
// manages state when enemy is walking

#ifndef _ENEMY_WALKING_STATE_
#define	_ENEMY_WALKING_STATE_

#include "State.h"

// forward declaration
class Enemy;

class EnemyWalkingState : public State<Enemy>
{
public:
	// static instance call
	static EnemyWalkingState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyWalkingState() {}
	~EnemyWalkingState() {}
	EnemyWalkingState(std::string name);
	EnemyWalkingState(const EnemyWalkingState&);
	EnemyWalkingState& operator=(const EnemyWalkingState&);
};

#endif // !_ENEMY_WALKING_STATE_