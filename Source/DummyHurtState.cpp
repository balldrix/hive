#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"

DummyHurtState* DummyHurtState::Instance()
{
	static DummyHurtState instance;
	return &instance;
}

void DummyHurtState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->SetAnimation("Hurt");
	enemy->GetHitBoxManager()->SetCurrentHitBox("Hurt");
}

void DummyHurtState::Execute(Dummy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
	{
		enemy->SetEnemyState(DummyIdleState::Instance());
	}
}

void DummyHurtState::OnExit(Dummy* enemy)
{
	enemy->GetAnimator()->Reset();
}


