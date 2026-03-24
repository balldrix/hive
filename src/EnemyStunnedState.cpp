#include "EnemyStunnedState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

EnemyStunnedState* EnemyStunnedState::Instance()
{
	static EnemyStunnedState instance("stunned");
	return &instance;
}

void EnemyStunnedState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);

	if(enemy->IsGrounded())
	{
		enemy->Stop();
	}
}

void EnemyStunnedState::Execute(Enemy* enemy)
{
	if(enemy->IsGrounded())
	{
		enemy->SetTargetVelocityX(0.0f);
		enemy->SetCurrentVelocity(0.0f, enemy->GetCurrentVelocity().y);
	}

	if(enemy->GetStunTimer() > 0.0f)
	{
		return;
	}

	enemy->SetStunTimer(0.0f);
	enemy->ResetStateChangeTimer();
	enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
}

void EnemyStunnedState::OnExit(Enemy* enemy)
{
}

EnemyStunnedState::EnemyStunnedState(const std::string& name)
{
	m_name = name;
}
