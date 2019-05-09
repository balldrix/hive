// PlayerAttackState.h
// Christopher Ball 2019
// Player normal attack state

#ifndef _PLAYER_JAB_STATE_
#define _PLAYER_JAB_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerAttackState : public State<Player>
{
public:
	// static instance call
	static PlayerAttackState* Instance();
	void SetName(std::string name);

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerAttackState() {}
	PlayerAttackState(std::string name);
	PlayerAttackState(const PlayerAttackState&);
	PlayerAttackState operator=(PlayerAttackState const&);
};

#endif // _PLAYER_JAB_STATE_
