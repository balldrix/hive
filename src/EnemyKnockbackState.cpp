#include "EnemyKnockbackState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyDeadState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"
#include <directxtk/SimpleMath.h>
#include "UnitVectors.h"

EnemyKnockbackState* EnemyKnockbackState::Instance()
{
	static EnemyKnockbackState instance("knockback");
	return &instance;
}

void EnemyKnockbackState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->SetGrounded(false);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->GetAnimator()->SetAnimation(m_name);
}

void EnemyKnockbackState::Execute(Enemy* enemy)
{
	if(enemy->GetCurrentVelocity().x < 0)
	{
		enemy->FlipHorizontally(false);
	} 
	else if(enemy->GetCurrentVelocity().x > 0)
	{
		enemy->FlipHorizontally(true);
	}

	if(enemy->IsGrounded())
	{
		enemy->DisplayDust(enemy->GetGroundPosition());

		if(enemy->GetKnockbackCount() == 0)
		{
			enemy->Kill();
		}

		if(!enemy->IsDead())
		{
			Vector2 direction = Vector2::Zero;

			if(enemy->GetCurrentVelocity().x > 0)
			{
				direction = UnitVectors::UpRight;
			}
			else
			{
				direction = UnitVectors::UpLeft;
			}

			enemy->Knockback(direction, 50.0f);
			enemy->SetKnockbackCount(enemy->GetKnockbackCount() - 1);
			enemy->GetAnimator()->Reset();
			enemy->SetGrounded(false);
		}
		else
		{
			enemy->GetStateMachine()->ChangeState(EnemyDeadState::Instance());
		}
	}
}

void EnemyKnockbackState::OnExit(Enemy* enemy)
{
}

EnemyKnockbackState::EnemyKnockbackState(const std::string &name)
{
	m_name = name;
}
