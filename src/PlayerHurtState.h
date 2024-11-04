#pragma once

#include "State.h"

#include <string>

class Player;

class PlayerHurtState : public State<Player>
{
public:
	static PlayerHurtState* Instance();

	virtual void OnEnter(Player* enemy);
	virtual void Execute(Player* enemy);
	virtual void OnExit(Player* enemy);

private:
	PlayerHurtState() {}
	~PlayerHurtState() {}
	PlayerHurtState(const std::string &name);
	PlayerHurtState(const PlayerHurtState&);
};