#pragma once

#include "State.h"

class Player;

class PlayerBlockState : public State<Player>
{
public:
	static PlayerBlockState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerBlockState() {}
	~PlayerBlockState() {}
	PlayerBlockState(const std::string& name);
	PlayerBlockState(const PlayerBlockState&);
	PlayerBlockState& operator=(const PlayerBlockState&);
};