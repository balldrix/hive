#pragma once

#include "State.h"

#include <string>

class Enemy;

class EnemyDeadState : public State<Enemy>
{
public:
	static EnemyDeadState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyDeadState() {}
	~EnemyDeadState() {}
	EnemyDeadState(const std::string& name);
	EnemyDeadState(const EnemyDeadState&);
};