// PlayerJabState.h
// Christopher Ball 2019
// Player jab punch state

#ifndef _PLAYER_JAB_STATE_
#define _PLAYER_JAB_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerJabState : public State<Player>
{
public:
	// static instance call
	static PlayerJabState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerJabState() {}
	PlayerJabState(std::string name);
	PlayerJabState(const PlayerJabState&);
	PlayerJabState operator=(PlayerJabState const&);
};

#endif // _PLAYER_JAB_STATE_
