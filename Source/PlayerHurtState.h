// PlayerHurtState.h
// Christopher Ball 2019
// Manages player hurt state

#ifndef _PLAYER_HURT_STATE_
#define	_PLAYER_HURT_STATE_

#include "State.h"

// forward declaration
class Player;

class PlayerHurtState : public State<Player>
{
public:
	// static instance call
	static PlayerHurtState* Instance();

	virtual void OnEnter(Player* enemy);
	virtual void Execute(Player* enemy);
	virtual void OnExit(Player* enemy);

private:
	PlayerHurtState() {}
	~PlayerHurtState() {}
	PlayerHurtState(std::string name);
	PlayerHurtState(const PlayerHurtState&);
	PlayerHurtState& operator=(const PlayerHurtState&);
};

#endif // !_PLAYER_HURT_STATE_

