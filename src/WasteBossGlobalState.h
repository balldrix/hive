#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossGlobalState : public State<Enemy>
{
public:
	static WasteBossGlobalState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossGlobalState() {}
	~WasteBossGlobalState() {}
	WasteBossGlobalState(const std::string& name);
	WasteBossGlobalState(const WasteBossGlobalState&);
};
