#pragma once

#include "State.h"

#include <string>

class Enemy;

class EnemyKnockbackState : public State<Enemy>
{
public:
	static EnemyKnockbackState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyKnockbackState() {}
	~EnemyKnockbackState() {}
	EnemyKnockbackState(const std::string& name);
	EnemyKnockbackState(const EnemyKnockbackState&);
};