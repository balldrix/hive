#pragma once

#include "State.h"

class Player;

class PlayerWalkingState : public State<Player>
{
public:
	static PlayerWalkingState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerWalkingState() {}
	~PlayerWalkingState() {}
	PlayerWalkingState(std::string name);
	PlayerWalkingState(const PlayerWalkingState&);
	PlayerWalkingState& operator=(const PlayerWalkingState&);
};