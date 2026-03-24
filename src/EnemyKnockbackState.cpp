#include "EnemyKnockbackState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyDeadState.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"
#include "UnitVectors.h"

#include <directxtk/SimpleMath.h>
#include <string>

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
	if(!enemy->IsGrounded())
	{
		return;
	}

	enemy->GetCamera()->StartShake(2.0f, 3.0f);
	enemy->DisplayDust(enemy->GetPosition());

	if(enemy->GetKnockbackCount() > 0)
	{
		Vector2 direction = enemy->GetCurrentVelocity().x > 0.0f ? UnitVectors::UpRight : UnitVectors::UpLeft;
		enemy->Knockback(direction, 50.0f);
		enemy->SetKnockbackCount(enemy->GetKnockbackCount() - 1);
		enemy->GetAnimator()->Reset();
		enemy->SetGrounded(false);
		return;
	}

	if(enemy->ShouldRecoverAfterKnockback())
	{
		enemy->SetRecoverAfterKnockback(false);
		enemy->ResetStateChangeTimer();
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		return;
	}

	enemy->Kill();
	enemy->GetStateMachine()->ChangeState(EnemyDeadState::Instance());
}

void EnemyKnockbackState::OnExit(Enemy* enemy)
{
}

EnemyKnockbackState::EnemyKnockbackState(const std::string &name)
{
	m_name = name;
}
