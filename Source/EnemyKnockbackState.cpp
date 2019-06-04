#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "HitBoxManager.h"
#include "Animator.h"

EnemyKnockbackState* EnemyKnockbackState::Instance()
{
	static EnemyKnockbackState instance("Knockback");
	return &instance;
}

void EnemyKnockbackState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->SetGrounded(false);
	enemy->GetHitBoxManager()->KillAll();
	enemy->GetAnimator()->SetAnimation(m_name);
}

void EnemyKnockbackState::Execute(Enemy* enemy)
{
	// true if moving to the left
	if(enemy->GetCurrentVelocity().x < 0)
	{
		enemy->FlipHorizontally(false);
	}

	// true if moving to the right
	if(enemy->GetCurrentVelocity().x > 0)
	{
		enemy->FlipHorizontally(true);
	}

	if(enemy->IsGrounded())
	{
		enemy->GetStateMachine()->ChangeState(EnemyDeadState::Instance());
	}
}

void EnemyKnockbackState::OnExit(Enemy* enemy)
{
}

EnemyKnockbackState::EnemyKnockbackState(std::string name)
{
	m_name = name;
}