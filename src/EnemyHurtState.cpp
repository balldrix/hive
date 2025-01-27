#include "EnemyHurtState.h"

#include "StateMachine.h"
#include "Enemy.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "EnemyIdleState.h"

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
	enemy->ResetTimer(0);
}

void EnemyHurtState::Execute(Enemy* enemy)
{
	//if(enemy->GetAnimator()->IsDone())
		//enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);

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
