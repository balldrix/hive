#pragma once

#include "State.h"

class Enemy;

class KingMookChargeState : public State<Enemy>
{
public:
	static KingMookChargeState* Instance();

	virtual void OnEnter(Enemy* enemy);
	virtual void Execute(Enemy* enemy);
	virtual void OnExit(Enemy* enemy);

private:
	KingMookChargeState() {}
	~KingMookChargeState() {}
	KingMookChargeState(const std::string &name);
	KingMookChargeState(const KingMookChargeState&);
};