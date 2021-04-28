#pragma once

#include "State.h"

class Player;

class PlayerGlobalState : public State<Player>
{
public:
	static PlayerGlobalState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerGlobalState() {}
	~PlayerGlobalState() {}
	PlayerGlobalState(const PlayerGlobalState&);
	PlayerGlobalState& operator=(const PlayerGlobalState&);
};