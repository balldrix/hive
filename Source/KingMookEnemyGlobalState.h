// Christopher Ball 2019-2020

#pragma once

#include "State.h"

class Enemy;

class KingMookEnemyGlobalState : public State<Enemy>
{
public:
	static KingMookEnemyGlobalState* Instance();

	virtual void OnEnter(Enemy* owner);
	virtual void Execute(Enemy* owner);
	virtual void OnExit(Enemy* owner);
	
private:
	KingMookEnemyGlobalState() {}
	~KingMookEnemyGlobalState() {}
	KingMookEnemyGlobalState(std::string name);
	KingMookEnemyGlobalState(const KingMookEnemyGlobalState&);
	KingMookEnemyGlobalState& operator=(const KingMookEnemyGlobalState&);
};