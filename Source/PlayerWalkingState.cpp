#include "PlayerOwnedStates.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerWalkingState* PlayerWalkingState::Instance()
{
	static PlayerWalkingState instance;
	return &instance;
}

void PlayerWalkingState::OnEnter(Player* player)
{
	// set walking animation
	player->GetAnimator()->SetAnimation("Walking");
	player->GetHitBox()->SetCurrentHitBox("Walking");
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
