#include "EnemyWalkingState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "NPCManager.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <string>

EnemyWalkingState* EnemyWalkingState::Instance()
{
	static EnemyWalkingState instance("walk");
	return &instance;
}

void EnemyWalkingState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	if(!enemy->IsRangedEnemy())
	{
		enemy->ResetStateChangeTimer();
	}
	enemy->SetMovementSpeed(enemy->GetData().walkSpeed);
}

void EnemyWalkingState::Execute(Enemy* enemy)
{
	enemy->ProcessSteering();

	const bool isRanged = enemy->GetData().enemyType == EnemyType::Ranged;
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(isRanged)
	{
		if(distance >= enemy->GetRangedPreferredRange() &&
			distance <= enemy->GetData().attackRange)
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		}

		return;
	}

	if(enemy->IsNormalMeleeEnemy() && enemy->IsCurrentWaveAttacker())
	{
		if(enemy->IsWithinAttackVerticalRange() && enemy->CanPreparedAttackHitPlayer())
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
			enemy->ResetStateChangeTimer();
		}

		return;
	}

	if(distance < enemy->GetData().fightRange &&
		(isRanged || !NPCManager::Instance()->IsAttackingEnemy(enemy)))
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		enemy->ResetStateChangeTimer();
		return;
	}
}

void EnemyWalkingState::OnExit(Enemy* enemy)
{
}

EnemyWalkingState::EnemyWalkingState(const std::string &name)
{
	m_name = name;
}
