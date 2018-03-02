#include "PlayerOwnedStates.h"
#include "Player.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerIdleState* PlayerIdleState::Instance()
{
	static PlayerIdleState instance;
	return &instance;
}

void PlayerIdleState::OnEnter(Player* player)
{
}

void PlayerIdleState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() != Vector2::Zero)
	{
		player->SetPlayerState(PlayerWalkingState::Instance());
	}
}

void PlayerIdleState::OnExit(Player* player)
{
}
