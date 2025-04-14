#pragma once

#include "State.h"

#include <string>

class Enemy;

class EnemyLandingState : public State<Enemy>
{
public:
	static EnemyLandingState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyLandingState() {}
	~EnemyLandingState() {}
	EnemyLandingState(const std::string& name);
	EnemyLandingState(const EnemyLandingState&);
};
