#pragma once

#include "State.h"

// forward declaration
class Enemy;

class EnemyKnockbackState : public State<Enemy>
{
public:
	// static instance call
	static EnemyKnockbackState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyKnockbackState() {}
	~EnemyKnockbackState() {}
	EnemyKnockbackState(std::string name);
	EnemyKnockbackState(const EnemyKnockbackState&);
	EnemyKnockbackState& operator=(const EnemyKnockbackState&);
};

