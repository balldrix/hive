#include "EnemyLandingState.h"

#include "Enemy.h"
#include "EnemyIdleState.h"
#include <string>

EnemyLandingState* EnemyLandingState::Instance()
{
	static EnemyLandingState instance("landing");
	return &instance;
}

void EnemyLandingState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->GetAnimator()->SetAnimation(m_name);
}

void EnemyLandingState::Execute(Enemy* enemy)
{
	if(enemy->GetAnimator()->IsDone())
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}
}

void EnemyLandingState::OnExit(Enemy* enemy)
{
}

EnemyLandingState::EnemyLandingState(const std::string& name)
{
	m_name = name;
}
