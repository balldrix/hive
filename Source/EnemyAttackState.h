#pragma once

#include "State.h"

class Enemy;

class EnemyAttackState : public State<Enemy>
{
public:
	// static instance call
	static EnemyAttackState* Instance();
	void SetAttack(const std::string &name);

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyAttackState() {}
	~EnemyAttackState() {}
	EnemyAttackState(const std::string &name);
	EnemyAttackState(const EnemyAttackState&);
	EnemyAttackState& operator=(const EnemyAttackState&);
};