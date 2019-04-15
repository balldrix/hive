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
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation("Jab");
	player->GetHitBoxManager()->SetCurrentHitBox("Jab");
	player->GetControlSystem()->CanAttack(false);
}

void PlayerJabState::Execute(Player* player)
{
	// stop movement
	player->SetTargetVelocity(Vector2::Zero);
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
