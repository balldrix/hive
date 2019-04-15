#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "Animator.h"
#include "HitBoxManager.h"

DummyDeadState* DummyDeadState::Instance()
{
	static DummyDeadState instance;
	return &instance;
}

void DummyDeadState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->SetAnimation("Dead");
	enemy->GetHitBoxManager()->KillAll();
}

void DummyDeadState::Execute(Dummy* enemy)
{
}

void DummyDeadState::OnExit(Dummy* enemy)
{
}
