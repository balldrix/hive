#include "EnemyFallingState.h"

#include "Enemy.h"
#include "EnemyLandingState.h"

#include <directxtk/SimpleMath.h>
#include <string>

EnemyFallingState* EnemyFallingState::Instance()
{
	static EnemyFallingState instance("falling");
	return &instance;
}

void EnemyFallingState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->SetGrounded(false);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->GetAnimator()->SetAnimation(m_name);
}

void EnemyFallingState::Execute(Enemy* enemy)
{
	if(enemy->IsGrounded())
	{
		enemy->DisplayDust(enemy->GetPosition());
		enemy->SetVelocity(Vector2::Zero);
		enemy->GetStateMachine()->ChangeState(EnemyLandingState::Instance());
	}
}

void EnemyFallingState::OnExit(Enemy* enemy)
{
}

EnemyFallingState::EnemyFallingState(const std::string& name)
{
	m_name = name;
}
