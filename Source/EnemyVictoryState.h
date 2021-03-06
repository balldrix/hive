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
	EnemyVictoryState(const std::string &name);
	EnemyVictoryState(const EnemyVictoryState&);
	EnemyVictoryState& operator=(const EnemyVictoryState&);
};