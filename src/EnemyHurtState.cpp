#include "EnemyHurtState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"

EnemyHurtState* EnemyHurtState::Instance()
{
	static EnemyHurtState instance("hurt");
	return &instance;
}

void EnemyHurtState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->ResetStateChangeTimer();
}

void EnemyHurtState::Execute(Enemy* enemy)
{
	if(enemy->GetPlayerTarget()->GetHitBoxManager()->IsHitBoxActive() == false)
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
}


void EnemyHurtState::OnExit(Enemy* enemy)
{
}

EnemyHurtState::EnemyHurtState(const std::string &name)
{
	m_name = name;
}
