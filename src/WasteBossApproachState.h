#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossApproachState : public State<Enemy>
{
public:
	static WasteBossApproachState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossApproachState() {}
	~WasteBossApproachState() {}
	WasteBossApproachState(const std::string& name);
	WasteBossApproachState(const WasteBossApproachState&);
};