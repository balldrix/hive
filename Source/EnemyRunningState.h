#pragma once

#include "State.h"

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
	EnemyRunningState(std::string name);
	EnemyRunningState(const EnemyRunningState&);
	EnemyRunningState& operator=(const EnemyRunningState&);
};