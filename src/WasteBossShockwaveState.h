#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossShockwaveState : public State<Enemy>
{
public:
	static WasteBossShockwaveState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossShockwaveState() {}
	~WasteBossShockwaveState() {}
	WasteBossShockwaveState(const std::string& name);
	WasteBossShockwaveState(const WasteBossShockwaveState&);
};