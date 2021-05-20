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
	// set jab animation
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
	
	// stop movement
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyAttackState::Execute(Enemy* enemy)
{
	// true if the attack animation is done
	if(enemy->GetAnimator()->IsDone())
	{
		// change back to idle state and reset control timers
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}
}

void EnemyAttackState::OnExit(Enemy* enemy)
{
}

EnemyAttackState::EnemyAttackState(const std::string &name)
{
	m_name = name;
}
