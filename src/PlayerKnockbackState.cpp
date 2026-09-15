#include "PlayerKnockbackState.h"

#include "Animator.h"
#include "HitBoxManager.h"
#include "Logger.h"
#include "Player.h"
#include "PlayerDeadState.h"
#include "PlayerIdleState.h"
#include "StateMachine.h"
#include "UnitVectors.h"

#include <directxtk/SimpleMath.h>
#include <string>

PlayerKnockbackState* PlayerKnockbackState::Instance()
{
	static PlayerKnockbackState instance("knockback");
	return &instance;
}

void PlayerKnockbackState::OnEnter(Player* player)
{
	player->GetAnimator()->Reset();
	player->SetGrounded(false);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
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

	if(!player->IsGrounded()) return;

	player->DisplayDust(player->GetPosition());
	player->ResetKnockoutTimer();

	if(player->GetKnockbackCount() < 1)
	{
		player->Stop();
		player->GetStateMachine()->ChangeState(PlayerDeadState::Instance());
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
		player->SetGrounded(false);
	}
}

void PlayerKnockbackState::OnExit(Player* player)
{
}

PlayerKnockbackState::PlayerKnockbackState(const std::string &name)
{
	m_name = name;
}
