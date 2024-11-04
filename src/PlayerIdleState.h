#pragma once

#include "State.h"

#include <string>

class Player;

class PlayerIdleState : public State<Player>
{
public:

	static PlayerIdleState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerIdleState() {}
	~PlayerIdleState() {}
	PlayerIdleState(const std::string &name);
	PlayerIdleState(const PlayerIdleState&);
};