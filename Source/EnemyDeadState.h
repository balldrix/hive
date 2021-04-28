#pragma once

#include "State.h"

// forward declaration
class Enemy;

class EnemyDeadState : public State<Enemy>
{
public:
	// static instance call
	static EnemyDeadState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyDeadState() {}
	~EnemyDeadState() {}
	EnemyDeadState(std::string name);
	EnemyDeadState(const EnemyDeadState&);
	EnemyDeadState& operator=(const EnemyDeadState&);
};
