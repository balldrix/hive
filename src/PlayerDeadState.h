#pragma once

#include "State.h"

#include <string>

class Player;

class PlayerDeadState : public State<Player>
{
public:
	static PlayerDeadState* Instance();

	virtual void OnEnter(Player* enemy);
	virtual void Execute(Player* enemy);
	virtual void OnExit(Player* enemy);

private:
	PlayerDeadState() {}
	~PlayerDeadState() {}
	PlayerDeadState(const std::string &name);
	PlayerDeadState(const PlayerDeadState&);
};