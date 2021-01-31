// EnemyVictoryState.h
// Christopher Ball 2019-2021

#pragma once

#include "State.h"

class Enemy;

class EnemyVictoryState : public State<Enemy>
{
public:
	static EnemyVictoryState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyVictoryState() {}
	~EnemyVictoryState() {}
	EnemyVictoryState(std::string name);
	EnemyVictoryState(const EnemyVictoryState&);
	EnemyVictoryState& operator=(const EnemyVictoryState&);
};