#include "EnemyOwnedStates.h"
#include "StateMachine.h"
#include "Enemy.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"

EnemyHurtState* EnemyHurtState::Instance()
{
	static EnemyHurtState instance("Hurt");
	return &instance;
}

void EnemyHurtState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->KillAll();
	enemy->ResetTimer();
}

void EnemyHurtState::Execute(Enemy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());

	if(enemy->GetPlayerTarget()->GetHitBoxManager()->IsHitBoxActive() == false)
		enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
}


void EnemyHurtState::OnExit(Enemy* enemy)
{
}

EnemyHurtState::EnemyHurtState(std::string name)
{
	m_name = name;
}
