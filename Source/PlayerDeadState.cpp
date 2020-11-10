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

void PlayerDeadState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->KillAll();
}

void PlayerDeadState::Execute(Player* player)
{
	// true if the knock back count is up
	if(player->GetKnockbackCount() < 1 && player->IsGrounded())
	{
		// stop all movement
		player->SetTargetVelocity(Vector2::Zero);
	}
	else
	{
		// calculate direction to knockback
		Vector2 direction = Vector2::Zero;

		if(player->GetCurrentVelocity().x > 0)
		{
			direction = UnitVectors::UpRight;
		}
		else
		{
			direction = UnitVectors::UpLeft;
		}

		// knockback with  50.0f force
		player->Knockback(direction, 30.0f);

		// reduce knock back amount
		player->SetKnockbackCount(player->GetKnockbackCount() - 1);

		// reset anim
		player->GetStateMachine()->ChangeState(PlayerKnockbackState::Instance());
	}
}

void PlayerDeadState::OnExit(Player* player)
{
}

PlayerDeadState::PlayerDeadState(std::string name)
{
	m_name = name;
}
