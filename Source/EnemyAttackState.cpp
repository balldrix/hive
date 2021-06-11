#include "EnemyAttackState.h"

#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "UnitVectors.h"
#include "StateMachine.h"

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
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
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