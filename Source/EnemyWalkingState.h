#pragma once

#include "State.h"

class Enemy;

class EnemyWalkingState : public State<Enemy>
{
public:
	static EnemyWalkingState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyWalkingState() {}
	~EnemyWalkingState() {}
	EnemyWalkingState(std::string name);
	EnemyWalkingState(const EnemyWalkingState&);
	EnemyWalkingState& operator=(const EnemyWalkingState&);
};