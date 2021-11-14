#pragma once

#include "State.h"

class Player;

class PlayerRunningState : public State<Player>
{
public:
	static PlayerRunningState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerRunningState() {}
	~PlayerRunningState() {}
	PlayerRunningState(const std::string &name);
	PlayerRunningState(const PlayerRunningState&);
	PlayerRunningState& operator=(const PlayerRunningState);
};