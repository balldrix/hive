#pragma once

#include "State.h"

#include <string>

class Enemy;

class EnemyFallingState : public State<Enemy>
{
public:
	static EnemyFallingState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyFallingState() {}
	~EnemyFallingState() {}
	EnemyFallingState(const std::string& name);
	EnemyFallingState(const EnemyFallingState&);
};
