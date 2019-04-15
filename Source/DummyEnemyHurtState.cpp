#include "DummyEnemyOwnedStates.h"
#include "DummyEnemy.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"

DummyEnemyHurtState* DummyEnemyHurtState::Instance()
{
	static DummyEnemyHurtState instance;
	return &instance;
}

void DummyEnemyHurtState::OnEnter(DummyEnemy* enemy)
{
	enemy->GetAnimator()->SetAnimation("Hurt");
	enemy->GetHitBoxManager()->SetCurrentHitBox("Hurt");
}

void DummyEnemyHurtState::Execute(DummyEnemy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
	{
		enemy->SetEnemyState(DummyEnemyIdleState::Instance());
	}
}

void DummyEnemyHurtState::OnExit(DummyEnemy* enemy)
{
	enemy->GetAnimator()->Reset();
}


