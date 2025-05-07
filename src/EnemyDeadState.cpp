#include "EnemyDeadState.h"

#include "Animator.h"
#include "Enemy.h"
#include "GameplayConstants.h"
#include "HitBoxManager.h"
#include "NPCManager.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace GameplayConstants;

EnemyDeadState* EnemyDeadState::Instance()
{
	static EnemyDeadState instance("dead");
	return &instance;
}

void EnemyDeadState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);

	if(enemy->GetHealth() <= 0)
		enemy->PlayDeathSound();

	if(NPCManager::Instance()->GetAttackingEnemy() == enemy)
		NPCManager::Instance()->SetNextAttackingEnemy();

	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyDeadState::Execute(Enemy* enemy)
{
	auto deadTimer = enemy->GetDeathTimer();

	if((EnemyDeadDuration - deadTimer) > EnemyFlashStartTime)
	{
		enemy->Flash();
	}

	if(deadTimer <= 0.0f)
	{
		enemy->SetActive(false);
	}
}

void EnemyDeadState::OnExit(Enemy* enemy)
{
}

EnemyDeadState::EnemyDeadState(const std::string &name)
{
	m_name = name;
}
