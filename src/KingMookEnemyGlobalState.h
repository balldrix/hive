#pragma once

#include "State.h"

class Enemy;

class KingMookEnemyGlobalState : public State<Enemy>
{
public:
	static KingMookEnemyGlobalState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);
	
private:
	KingMookEnemyGlobalState() {}
	~KingMookEnemyGlobalState() {}
};