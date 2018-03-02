#include "PlayerOwnedStates.h"
#include "Player.h"
#include "ControlSystem.h"
#include "Sprite.h"
#include "UnitVectors.h"

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
	if(player->GetCurrentVelocity() == Vector2::Zero)
	{
		player->SetPlayerState(PlayerIdleState::Instance());
	}
}

void PlayerWalkingState::OnExit(Player* player)
{
}
