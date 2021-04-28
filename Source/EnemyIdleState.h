#pragma once

#include "State.h"

// forward declaration
class Enemy;

class EnemyIdleState : public State<Enemy>
{
public:
	// static instance call
	static EnemyIdleState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyIdleState() {}
	~EnemyIdleState() {}
	EnemyIdleState(std::string name);
	EnemyIdleState(const EnemyIdleState&);
	EnemyIdleState& operator=(const EnemyIdleState&);
};

