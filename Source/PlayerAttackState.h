#pragma once

#include "State.h"

// forward declaration
class Player;

class PlayerAttackState : public State<Player>
{
public:
	// static instance call
	static PlayerAttackState* Instance();
	void SetAttack(std::string name);

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerAttackState() {}
	~PlayerAttackState() {}
	PlayerAttackState(std::string name);
	PlayerAttackState(const PlayerAttackState&);
	PlayerAttackState& operator=(const PlayerAttackState&);
};