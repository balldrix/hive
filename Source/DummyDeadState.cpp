#include "DummyOwnedStates.h"
#include "Dummy.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "UnitVectors.h"

DummyDeadState* DummyDeadState::Instance()
{
	static DummyDeadState instance("Dead");
	return &instance;
}

void DummyDeadState::OnEnter(Dummy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->KillAll();
}

void DummyDeadState::Execute(Dummy* enemy)
{
	// true if the knock back count is up
	if(enemy->GetKnockbackCount() < 1 && enemy->IsGrounded())
	{
		// stop all movement
		enemy->SetTargetVelocity(Vector2::Zero);
	}
	else
	{
		// calculate direction to knockback
		Vector2 direction = Vector2(enemy->GetCurrentVelocity().x, -0.9f);
		direction.Normalize();

		// knockback dummy with  50.0f force
		enemy->Knockback(direction, 50.0f);

		// reduce knock back amount
		enemy->SetKnockbackCount(enemy->GetKnockbackCount() - 1);

		// reset anim
		enemy->GetStateMachine()->ChangeState(DummyKnockbackState::Instance());
	}
}

void DummyDeadState::OnExit(Dummy* enemy)
{
}

DummyDeadState::DummyDeadState(std::string name)
{
	m_name = name;
}
