#include "EnemyAttackRunState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyRunningState.h"
#include "StateMachine.h"

#include <string>

EnemyAttackRunState* EnemyAttackRunState::Instance()
{
	static EnemyAttackRunState instance("attackRun");
	return &instance;

}

void EnemyAttackRunState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->SetMovementSpeed(enemy->GetData().chargeSpeed);
}

void EnemyAttackRunState::Execute(Enemy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
		enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
}

void EnemyAttackRunState::OnExit(Enemy* enemy)
{
}

EnemyAttackRunState::EnemyAttackRunState(const std::string& name)
{
	m_name = name;
}
