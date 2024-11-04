#pragma once

#include "State.h"

#include <string>

class Enemy;

class EnemyRunningState : public State<Enemy>
{
public:
	static EnemyRunningState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyRunningState() {}
	~EnemyRunningState() {}
	EnemyRunningState(const std::string &name);
	EnemyRunningState(const EnemyRunningState&);
};