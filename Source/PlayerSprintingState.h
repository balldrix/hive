#pragma once

#include "State.h"

class Player;

class PlayerSprintingState : public State<Player>
{
public:
	static PlayerSprintingState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerSprintingState() {}
	~PlayerSprintingState() {}
	PlayerSprintingState(const std::string &name);
	PlayerSprintingState(const PlayerSprintingState&);
	PlayerSprintingState& operator=(const PlayerSprintingState);
};