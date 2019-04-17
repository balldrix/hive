// PlayerWalkingState.h
// Christopher Ball 2018
// Player walking state

#ifndef _PLAYER_WALKING_STATE_
#define _PLAYER_WALKING_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerWalkingState : public State<Player>
{
public:
	// static instance call
	static PlayerWalkingState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerWalkingState() {}
	PlayerWalkingState(std::string name);
	PlayerWalkingState(const PlayerWalkingState&);
	PlayerWalkingState operator=(PlayerWalkingState const&);
};

#endif // !_PLAYER_WALKING_STATE_
