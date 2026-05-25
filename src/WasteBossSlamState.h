#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossSlamState : public State<Enemy>
{
public:
	static WasteBossSlamState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossSlamState() {}
	~WasteBossSlamState() {}
	WasteBossSlamState(const std::string& name);
	WasteBossSlamState(const WasteBossSlamState&);
};