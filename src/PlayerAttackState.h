#pragma once

#include "State.h"

class Player;

class PlayerAttackState : public State<Player>
{
public:
	static PlayerAttackState* Instance();
	void SetAttack(const std::string &name);

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerAttackState() {}
	~PlayerAttackState() {}
	PlayerAttackState(const std::string &name);
	PlayerAttackState(const PlayerAttackState&);
	PlayerAttackState& operator=(const PlayerAttackState&);
};