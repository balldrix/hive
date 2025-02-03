#pragma once

#include "State.h"

class Player;

class PlayerBuildSpecialState : public State<Player>
{
public:
	static PlayerBuildSpecialState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerBuildSpecialState() {}
	~PlayerBuildSpecialState() {}
	PlayerBuildSpecialState(const std::string& name);
	PlayerBuildSpecialState(const PlayerBuildSpecialState&);
};