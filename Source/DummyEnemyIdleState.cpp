#include "DummyEnemyOwnedStates.h"
#include "DummyEnemy.h"
#include "HitBoxManager.h"
#include "Animator.h"

DummyEnemyIdleState* DummyEnemyIdleState::Instance()
{
	static DummyEnemyIdleState instance;
	return &instance;
}

void DummyEnemyIdleState::OnEnter(DummyEnemy* enemy)
{
	enemy->GetAnimator()->SetAnimation("Idle");
	enemy->GetHitBoxManager()->SetCurrentHitBox("Idle");
}

void DummyEnemyIdleState::Execute(DummyEnemy* enemy)
{
}


void DummyEnemyIdleState::OnExit(DummyEnemy* enemy)
{
	enemy->GetAnimator()->Reset();
}
