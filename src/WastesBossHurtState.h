#pragma once

#include "State.h"

#include <string>

class Enemy;

class WasteBossHurtState : public State<Enemy>
{
public:
	static WasteBossHurtState* Instance();

	virtual void OnEnter(Enemy* boss) override;
	virtual void Execute(Enemy* boss) override;
	virtual void OnExit(Enemy* boss) override;

private:
	WasteBossHurtState() {}
	~WasteBossHurtState() {}
	WasteBossHurtState(const std::string& name);
	WasteBossHurtState(const WasteBossHurtState&);
};