#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "Animator.h"
#include "HitBoxManager.h"

DummyDeadState* DummyDeadState::Instance()
{
	static DummyDeadState instance("Dead");
	return &instance;
}

void DummyDeadState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->KillAll();
}

void DummyDeadState::Execute(Dummy* enemy)
{
}

void DummyDeadState::OnExit(Dummy* enemy)
{
}

DummyDeadState::DummyDeadState(std::string name)
{
	m_name = name;
}
