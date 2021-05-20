#pragma once

#include "State.h"

// forward declaration
class Enemy;

class EnemyHurtState : public State<Enemy>
{
public:
	// static instance call
	static EnemyHurtState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyHurtState() {}
	~EnemyHurtState() {}
	EnemyHurtState(const std::string &name);
	EnemyHurtState(const EnemyHurtState&);
	EnemyHurtState& operator=(const EnemyHurtState&);
};