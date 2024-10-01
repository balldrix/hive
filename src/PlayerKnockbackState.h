#pragma once

#include "State.h"

class Player;

class PlayerKnockbackState : public State<Player>
{
public:
	static PlayerKnockbackState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerKnockbackState() {}
	~PlayerKnockbackState() {}
	PlayerKnockbackState(const std::string &name);
	PlayerKnockbackState(const PlayerKnockbackState&);
	PlayerKnockbackState& operator=(const PlayerKnockbackState&);
};