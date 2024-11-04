#pragma once

#include "State.h"

#include <string>

class Enemy;

class RunningEnemyDeadState : public State<Enemy>
{
public:
	static RunningEnemyDeadState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	RunningEnemyDeadState() {}
	~RunningEnemyDeadState() {}
	RunningEnemyDeadState(const std::string& name);
	RunningEnemyDeadState(const RunningEnemyDeadState&);
};
