#pragma once

#include "State.h"

class Enemy;

class MookRunningEnemyGlobalState : public State<Enemy>
{
public:
	// static instance call
	static MookRunningEnemyGlobalState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	MookRunningEnemyGlobalState() {}
	~MookRunningEnemyGlobalState() {}
	MookRunningEnemyGlobalState(const MookRunningEnemyGlobalState&);
	MookRunningEnemyGlobalState& operator=(const MookRunningEnemyGlobalState&);
};