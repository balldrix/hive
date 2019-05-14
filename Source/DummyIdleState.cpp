#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "HitBoxManager.h"
#include "Animator.h"

DummyIdleState* DummyIdleState::Instance()
{
	static DummyIdleState instance("Idle");
	return &instance;
}

void DummyIdleState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
}

void DummyIdleState::Execute(Dummy* enemy)
{
}


void DummyIdleState::OnExit(Dummy* enemy)
{
}

DummyIdleState::DummyIdleState(std::string name)
{
	m_name = name;
}
