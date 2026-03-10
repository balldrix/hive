#include "EnemyIdleState.h"

#include "Animator.h"
#include "directxtk/SimpleMath.h"
#include "Enemy.h"
#include "EnemyRunningState.h"
#include "EnemyWalkingState.h"
#include "GameplayConstants.h"
#include "HitBoxManager.h"
#include "NPCManager.h"
#include "StateMachine.h"

#include <cmath>
#include <string>

using namespace DirectX::SimpleMath;
using namespace GameplayConstants;

EnemyIdleState* EnemyIdleState::Instance()
{
	static EnemyIdleState instance("idle");
	return &instance;
}

void EnemyIdleState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->ResetStateChangeTimer();
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyIdleState::Execute(Enemy* enemy)
{
	if(enemy->GetTimer() > 0 || enemy->GetHealth() < 0)
		return;

	const bool isRanged = enemy->GetData().enemyType == EnemyType::Ranged;
	auto verticalDistance = fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY());
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(distance > enemy->GetData().fightRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
		return;
	}

	if(isRanged)
	{
		enemy->Stop();
		enemy->ResetStateChangeTimer();
		enemy->Attack();
		return;
	}

	Enemy* attackingEnemy = NPCManager::Instance()->GetAttackingEnemy(enemy->GetWaveId());

	if(attackingEnemy != enemy)
	{
		enemy->ResetStateChangeTimer();

		if(attackingEnemy == nullptr)
		{
			NPCManager::Instance()->SetAttackingEnemy(enemy);
		}

		return;
	}

	if((distance > enemy->GetData().attackRange && distance < enemy->GetData().fightRange) || (distance < enemy->GetData().attackRange && verticalDistance > VerticalHitRange))
	{
		enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
		return;
	}

	if(distance < enemy->GetData().attackRange && verticalDistance < VerticalHitRange)
	{
		enemy->Stop();
		enemy->ResetStateChangeTimer();
		enemy->Attack();
		return;
	}
}

void EnemyIdleState::OnExit(Enemy* enemy)
{
}

EnemyIdleState::EnemyIdleState(const std::string& name)
{
	m_name = name;
}
