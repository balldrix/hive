#include "EnemyAttackState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <string>

EnemyAttackState* EnemyAttackState::Instance()
{
	static EnemyAttackState instance;
	return &instance;
}

void EnemyAttackState::SetAttack(const std::string &name)
{
	m_name = name;
}

void EnemyAttackState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->SetTargetVelocity(Vector2::Zero);
	enemy->PlayPunchSound();
}

void EnemyAttackState::Execute(Enemy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
}

void EnemyAttackState::OnExit(Enemy* enemy)
{
}

EnemyAttackState::EnemyAttackState(const std::string &name)
{
	m_name = name;
}