#include "PlayerOwnedStates.h"
#include "StateMachine.h"
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
	if(player->GetCurrentVelocity().x < 0)
	{
		player->FlipHorizontally(false);
	}

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

PlayerKnockbackState::PlayerKnockbackState(const std::string &name)
{
	m_name = name;
}
