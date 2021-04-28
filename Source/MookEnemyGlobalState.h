#pragma once

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