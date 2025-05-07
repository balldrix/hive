#pragma once

#include "State.h"

class Enemy;

class NormalEnemyGlobalState : public State<Enemy>
{
public:
	static NormalEnemyGlobalState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	NormalEnemyGlobalState() {}
	~NormalEnemyGlobalState() {}
	NormalEnemyGlobalState(const NormalEnemyGlobalState&);
};