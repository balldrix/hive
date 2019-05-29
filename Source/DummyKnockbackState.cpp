#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "HitBoxManager.h"
#include "Animator.h"

DummyKnockbackState* DummyKnockbackState::Instance()
{
	static DummyKnockbackState instance("Knockback");
	return &instance;
}

void DummyKnockbackState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->SetGrounded(false);
	enemy->GetHitBoxManager()->KillAll();
	enemy->GetAnimator()->SetAnimation(m_name);
}

void DummyKnockbackState::Execute(Dummy* enemy)
{
	// true if moving to the left
	if(enemy->GetCurrentVelocity().x < 0)
	{
		enemy->FlipHorizontally(true);
	}

	// true if moving to the right
	if(enemy->GetCurrentVelocity().x > 0)
	{
		enemy->FlipHorizontally(false);
	}

	if(enemy->IsGrounded())
	{
		enemy->GetStateMachine()->ChangeState(DummyDeadState::Instance());
	}
}

void DummyKnockbackState::OnExit(Dummy* enemy)
{
}

DummyKnockbackState::DummyKnockbackState(std::string name)
{
	m_name = name;
}
