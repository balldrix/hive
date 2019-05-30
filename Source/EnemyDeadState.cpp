#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "UnitVectors.h"

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
}

void EnemyDeadState::Execute(Enemy* enemy)
{
	// true if the knock back count is up
	if(enemy->GetKnockbackCount() < 1 && enemy->IsGrounded())
	{
		// stop all movement
		enemy->SetTargetVelocity(Vector2::Zero);
	}
	else
	{
		// calculate direction to knockback
		Vector2 direction = Vector2(enemy->GetCurrentVelocity().x, -0.9f);
		direction.Normalize();

		// knockback dummy with  50.0f force
		enemy->Knockback(direction, 50.0f);

		// reduce knock back amount
		enemy->SetKnockbackCount(enemy->GetKnockbackCount() - 1);

		// reset anim
		enemy->GetStateMachine()->ChangeState(EnemyKnockbackState::Instance());
	}
}

void EnemyDeadState::OnExit(Enemy* enemy)
{
}

EnemyDeadState::EnemyDeadState(std::string name)
{
	m_name = name;
}
