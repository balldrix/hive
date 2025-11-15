#pragma once

#include "State.h"

#include <string>

class Player;

class PlayerPickupState : public State<Player>
{
public:
	static PlayerPickupState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerPickupState() {}
	~PlayerPickupState() {}
	PlayerPickupState(const std::string& name);
	PlayerPickupState(const PlayerPickupState&);
};