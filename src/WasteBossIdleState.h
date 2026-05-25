#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossIdleState : public State<Enemy>
{
public:
	static WasteBossIdleState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossIdleState() {}
	~WasteBossIdleState() {}
	WasteBossIdleState(const std::string& name);
	WasteBossIdleState(const WasteBossIdleState&);
};