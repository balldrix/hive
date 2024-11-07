#include "EnemyKnockbackState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyDeadState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"

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
		enemy->GetStateMachine()->ChangeState(EnemyDeadState::Instance());
	}
}

void EnemyKnockbackState::OnExit(Enemy* enemy)
{
}

EnemyKnockbackState::EnemyKnockbackState(const std::string &name)
{
	m_name = name;
}
