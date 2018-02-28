#include "PlayerWalkingState.h"
#include "Player.h"

PlayerWalkingState* PlayerWalkingState::Instance()
{
	static PlayerWalkingState instance;
	return &instance;
}

void PlayerWalkingState::OnEnter(Player* player)
{

}

void PlayerWalkingState::Execute(Player* player)
{
}

void PlayerWalkingState::OnExit(Player* player)
{
}
