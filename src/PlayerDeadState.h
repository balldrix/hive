#pragma once

#include "State.h"

#include <string>

class Player;

class PlayerDeadState : public State<Player>
{
public:
	static PlayerDeadState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerDeadState() {}
	~PlayerDeadState() {}
	PlayerDeadState(const std::string &name);
	PlayerDeadState(const PlayerDeadState&);
};