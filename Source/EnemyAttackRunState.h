#pragma once

#include "State.h"

class Enemy;

class EnemyAttackRunState : public State<Enemy>
{
public:
	static EnemyAttackRunState* Instance();
	
	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyAttackRunState() {}
	~EnemyAttackRunState() {}
	EnemyAttackRunState(const std::string& name);
	EnemyAttackRunState(const EnemyAttackRunState&);
	EnemyAttackRunState& operator=(const EnemyAttackRunState&);
};