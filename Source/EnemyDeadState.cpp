#include "EnemyDeadState.h"

#include "StateMachine.h"
#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "UnitVectors.h"
#include "InGameHudManager.h"

EnemyDeadState* EnemyDeadState::Instance()
{
	static EnemyDeadState instance("dead");
	return &instance;
}

void EnemyDeadState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->KillAll();

	if(enemy->GetHealth() <= 0)
		enemy->PlayDeathSound();
}

void EnemyDeadState::Execute(Enemy* enemy)
{
	if(enemy->IsDead())
	{
		enemy->SetTargetVelocity(Vector2::Zero);
	}
	else
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
		enemy->GetStateMachine()->ChangeState(EnemyKnockbackState::Instance());
		
		if(enemy->GetKnockbackCount() < 1)
			enemy->Kill();
	}
}

void EnemyDeadState::OnExit(Enemy* enemy)
{
}

EnemyDeadState::EnemyDeadState(const std::string &name)
{
	m_name = name;
}
