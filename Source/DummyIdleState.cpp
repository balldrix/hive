#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "HitBoxManager.h"
#include "Animator.h"

DummyIdleState* DummyIdleState::Instance()
{
	static DummyIdleState instance;
	return &instance;
}

void DummyIdleState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->SetAnimation("Idle");
	enemy->GetHitBoxManager()->SetCurrentHitBox("Idle");
}

void DummyIdleState::Execute(Dummy* enemy)
{
}


void DummyIdleState::OnExit(Dummy* enemy)
{
	enemy->GetAnimator()->Reset();
}
