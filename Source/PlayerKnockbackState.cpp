#include "PlayerOwnedStates.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"

PlayerKnockbackState* PlayerKnockbackState::Instance()
{
	static PlayerKnockbackState instance("Knockback");
	return &instance;
}

void PlayerKnockbackState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->SetGrounded(false);
	player->GetHitBoxManager()->KillAll();
	player->GetAnimator()->SetAnimation(m_name);
}

void PlayerKnockbackState::Execute(Player* player)
{
	// true if moving to the left
	if(player->GetCurrentVelocity().x < 0)
	{
		player->FlipHorizontally(false);
	}

	// true if moving to the right
	if(player->GetCurrentVelocity().x > 0)
	{
		player->FlipHorizontally(true);
	}

	if(player->IsGrounded())
	{
		player->GetStateMachine()->ChangeState(PlayerDeadState::Instance());
	}
}

void PlayerKnockbackState::OnExit(Player* player)
{
}

PlayerKnockbackState::PlayerKnockbackState(std::string name)
{
	m_name = name;
}
