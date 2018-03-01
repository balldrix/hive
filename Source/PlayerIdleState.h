// PlayerIdleState.h
// Christopher Ball 2018
// Player state when Idle

#ifndef _PLAYER_IDLE_STATE_
#define	_PLAYER_IDLE_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerIdleState : public State<Player>
{
public:
	// static instance call
	static PlayerIdleState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerIdleState() {}
	PlayerIdleState(const PlayerIdleState&);
	PlayerIdleState operator=(PlayerIdleState const&);
};

#endif // !_PLAYER_IDLE_STATE_
