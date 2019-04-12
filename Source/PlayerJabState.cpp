#include "PlayerOwnedStates.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerJabState* PlayerJabState::Instance()
{
	static PlayerJabState instance;
	return &instance;
}

void PlayerJabState::OnEnter(Player* player)
{
	// set jab animation
	player->GetAnimator()->SetAnimation("Jab");
	player->GetHitBox()->SetCurrentHitBox("Jab");
}

void PlayerJabState::Execute(Player* player)
{
	// stop movement
	player->SetCurrentVelocity(Vector2::Zero);

	// true if the jab animation is done
	if(player->GetAnimator()->IsDone())
	{
		player->SetPlayerState(PlayerIdleState::Instance());
	}
}

void PlayerJabState::OnExit(Player* player)
{
}
