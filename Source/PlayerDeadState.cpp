#include "PlayerOwnedStates.h"
#include "StateMachine.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "UnitVectors.h"

PlayerDeadState* PlayerDeadState::Instance()
{
	static PlayerDeadState instance("Dead");
	return &instance;
}

PlayerDeadState::PlayerDeadState(const std::string &name)
{
	m_name = name;
}

void PlayerDeadState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->KillAll();
	player->ResetKnockoutTimer();

	if(player->GetHealth() <= 0)
		player->PlayDeathSound();
}

void PlayerDeadState::Execute(Player* player)
{
	if(player->GetKnockbackCount() < 1 && player->IsGrounded())
	{
		player->SetTargetVelocity(Vector2::Zero);
	}
	else
	{
		Vector2 direction = Vector2::Zero;

		if(player->GetCurrentVelocity().x > 0)
		{
			direction = UnitVectors::UpRight;
		}
		else
		{
			direction = UnitVectors::UpLeft;
		}

		player->Knockback(direction, 30.0f);
		player->SetKnockbackCount(player->GetKnockbackCount() - 1);
		player->GetStateMachine()->ChangeState(PlayerKnockbackState::Instance());
	}
}

void PlayerDeadState::OnExit(Player* player)
{
}
