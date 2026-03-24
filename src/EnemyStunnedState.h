#pragma once

#include "State.h"

#include <string>

class Enemy;

class EnemyStunnedState : public State<Enemy>
{
public:
	static EnemyStunnedState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	EnemyStunnedState() {}
	~EnemyStunnedState() {}
	EnemyStunnedState(const std::string& name);
	EnemyStunnedState(const EnemyStunnedState&);
};
