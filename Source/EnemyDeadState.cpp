#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "UnitVectors.h"
#include "InGameHudManager.h"

EnemyDeadState* EnemyDeadState::Instance()
{
	static EnemyDeadState instance("Dead");
	return &instance;
}

void EnemyDeadState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->KillAll();
	
	if(enemy->GetHealth() < 1)
		enemy->Kill();
}

void EnemyDeadState::Execute(Enemy* enemy)
{
	// true if the knock back count is up
	if(enemy->IsDead())
	{
		// stop all movement
		enemy->SetTargetVelocity(Vector2::Zero);
	}
	else
	{
		// calculate direction to knockback
		Vector2 direction = Vector2::Zero;
		
		if(enemy->GetCurrentVelocity().x > 0)
		{
			direction = UnitVectors::UpRight;
		}
		else
		{
			direction = UnitVectors::UpLeft;
		}

		// knockback dummy with  50.0f force
		enemy->Knockback(direction, 50.0f);

		// reduce knock back amount
		enemy->SetKnockbackCount(enemy->GetKnockbackCount() - 1);

		// reset anim
		enemy->GetStateMachine()->ChangeState(EnemyKnockbackState::Instance());
		
		if(enemy->GetKnockbackCount() < 1)
			enemy->SetDead();
	}
}

void EnemyDeadState::OnExit(Enemy* enemy)
{
}

EnemyDeadState::EnemyDeadState(std::string name)
{
	m_name = name;
}
