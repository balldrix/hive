#include "DummyEnemyOwnedStates.h"

DummyEnemyDeadState* DummyEnemyDeadState::Instance()
{
	static DummyEnemyDeadState instance;
	return &instance;
}

void DummyEnemyDeadState::OnEnter(DummyEnemy* enemy)
{
	enemy->GetAnimator->SetAnimation("Dead");
	enemy->GetHitBoxManager()->Kill();
}

void DummyEnemyDeadState::Execute(DummyEnemy* enemy)
{
}

void DummyEnemyDeadState::OnExit(DummyEnemy* enemy)
{
}
