#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "Player.h"
#include "Animator.h"
#include "HitBoxManager.h"

DummyHurtState* DummyHurtState::Instance()
{
	static DummyHurtState instance("Hurt");
	return &instance;
}

void DummyHurtState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->KillAll();
}

void DummyHurtState::Execute(Dummy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
	{
		enemy->GetStateMachine()->ChangeState(DummyIdleState::Instance());
	}
}

void DummyHurtState::OnExit(Dummy* enemy)
{
	enemy->GetAnimator()->Reset();
}

DummyHurtState::DummyHurtState(std::string name)
{
	m_name = name;
}


