#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossJabState : public State<Enemy>
{
public:
	static WasteBossJabState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossJabState() {}
	~WasteBossJabState() {}
	WasteBossJabState(const std::string& name);
	WasteBossJabState(const WasteBossJabState&);
};