// PlayerDeadState.h
// Christopher Ball 2019
// manages state when player is dead

#ifndef _PLAYER_DEAD_STATE_
#define	_PLAYER_DEAD_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerDeadState : public State<Player>
{
public:
	// static instance call
	static PlayerDeadState* Instance();

	virtual void OnEnter(Player* enemy);
	virtual void Execute(Player* enemy);
	virtual void OnExit(Player* enemy);

private:
	PlayerDeadState() {}
	~PlayerDeadState() {}
	PlayerDeadState(std::string name);
	PlayerDeadState(const PlayerDeadState&);
	PlayerDeadState& operator=(const PlayerDeadState&);
};

#endif // !_PLAYER_DEAD_STATE_