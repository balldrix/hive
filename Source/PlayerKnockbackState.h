// PlayerKnockbackState.h
// Christopher Ball 2019
// manages what happens when the player is knocked back

#ifndef _PLAYER_KNOCKBACK_STATE_
#define	_PLAYER_KNOCKBACK_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerKnockbackState : public State<Player>
{
public:
	// static instance call
	static PlayerKnockbackState* Instance();

	virtual void OnEnter(Player* player);
	virtual void Execute(Player* player);
	virtual void OnExit(Player* player);

private:
	PlayerKnockbackState() {}
	~PlayerKnockbackState() {}
	PlayerKnockbackState(std::string name);
	PlayerKnockbackState(const PlayerKnockbackState&);
	PlayerKnockbackState& operator=(const PlayerKnockbackState&);
};

#endif // !_PLAYER_KNOCKBACK_STATE_