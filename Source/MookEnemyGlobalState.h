// MookEnemyGlobalState.h
// Christopher Ball 2019
// global state for common enemy methods

#ifndef _ENEMY_GLOBAL_STATE_
#define	_ENEMY_GLOBAL_STATE_

#include "State.h"

class Enemy;

class MookEnemyGlobalState : public State<Enemy>
{
public:
	// static instance call
	static MookEnemyGlobalState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	MookEnemyGlobalState() {}
	~MookEnemyGlobalState() {}
	MookEnemyGlobalState(const MookEnemyGlobalState&);
	MookEnemyGlobalState& operator=(const MookEnemyGlobalState&);
};
#endif // !_ENEMY_GLOBAL_STATE_
