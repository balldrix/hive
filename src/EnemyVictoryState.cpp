#include "EnemyVictoryState.h"

#include "Enemy.h"
#include "Animator.h"

EnemyVictoryState* EnemyVictoryState::Instance()
{
	static EnemyVictoryState instance("Victory");
	return &instance;
}

void EnemyVictoryState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
}

void EnemyVictoryState::Execute(Enemy* enemy)
{
	
}

void EnemyVictoryState::OnExit(Enemy* enemy)
{
}

EnemyVictoryState::EnemyVictoryState(const std::string &name)
{
	m_name = name;
}