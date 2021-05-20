#pragma once

#include "State.h"

class Enemy;

class EnemyIdleState : public State<Enemy>
{
public:
	static EnemyIdleState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyIdleState() {}
	~EnemyIdleState() {}
	EnemyIdleState(const std::string &name);
	EnemyIdleState(const EnemyIdleState&);
	EnemyIdleState& operator=(const EnemyIdleState&);
};

