#pragma once

#include "State.h"

class Player;

class PlayerDodgeState : public State<Player>
{
public:
	static PlayerDodgeState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerDodgeState() {}
	~PlayerDodgeState() {}
	PlayerDodgeState(const std::string& name);
	PlayerDodgeState(const PlayerDodgeState&);
	PlayerDodgeState& operator=(const PlayerDodgeState&);
};