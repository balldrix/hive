// PlayerGlobalState.h
// Christopher Ball 2019
// global state for common player methods

#ifndef _PLAYER_GLOBAL_STATE_
#define	_PLAYER_GLOBAL_STATE_

#include "State.h"

class Player;

class PlayerGlobalState : public State<Player>
{
public:
	// static instance call
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
#endif // !_PLAYER_GLOBAL_STATE_
