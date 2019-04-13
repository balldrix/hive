#include "PlayerOwnedStates.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerIdleState* PlayerIdleState::Instance()
{
	static PlayerIdleState instance;
	return &instance;
}

void PlayerIdleState::OnEnter(Player* player)
{
	// set idle animation
	player->GetAnimator()->SetAnimation("Idle");
	player->GetHitBox()->SetCurrentHitBox("Idle");
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
	player->GetAnimator()->Reset();
}
