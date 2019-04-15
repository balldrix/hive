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
	player->GetAnimator()->SetAnimation("Walking");
	player->GetHitBoxManager()->SetCurrentHitBox("Walking");
}

void PlayerWalkingState::Execute(Player* player)
{
	if(player->GetCurrentVelocity() == Vector2::Zero &&
		player->GetTargetVelocity() == Vector2::Zero)
	{
		player->SetPlayerState(PlayerIdleState::Instance());
	}
}

void PlayerWalkingState::OnExit(Player* player)
{
	player->GetAnimator()->Reset();
}
