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

	auto verticalDistance = fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY());
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(distance > enemy->GetData().fightRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
		return;
	}

	Enemy* attackingEnemy = NPCManager::Instance()->GetAttackingEnemy();

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

	//if(enemy->GetPlayerTarget()->GetKnockbackCount() < 1 && enemy->GetPlayerTarget()->GetHealth() < 1)
	//	return;

	//if((enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() == PlayerKnockbackState::Instance() ||
	//	enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() == PlayerDeadState::Instance())) return;

	//if(enemy->GetTimer() > 0 ||
	//	enemy->GetHealth() < 0)
	//	return;

	//if((enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
	//	enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance()))
	//{
	//	// true if enemy is outside hostile range
	//	if(distance > enemy->GetData().hostileRange)
	//	{
	//		enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
	//		enemy->ResetStateChangeTimer(Randomiser::GetRandNumUniform(0.4f, 1.0f));
	//	}
	//	else if(distance > enemy->GetData().fightRange || (NPCManager::Instance()->GetAttackingEnemy() == enemy && distance > enemy->GetData().attackRange))
	//	{
	//		enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
	//		enemy->ResetStateChangeTimer(Randomiser::GetRandNumUniform(0.4f, 1.0f));
	//	}
	//}

	//if(enemy->IsHostile() == false)
	//	return;

	//auto enemies = enemy->GetManager()->GetEnemyList();

	//if(distance < enemy->GetData().fightRange
	//	&& verticalDistance < VerticalHitRange
	//	&& NPCManager::Instance()->GetAttackingEnemy() == enemy)
	//{
	//	double randnum = Randomiser::GetRandNumUniform(0.02, 1.8);
	//
	//	enemy->Stop();
	//	enemy->ResetStateChangeTimer((float)randnum);
	//	enemy->Attack();
	//	return;
	//}

	//for(auto it = enemies.begin(); it != enemies.end(); it++)
	//{
	//	if(*it == enemy) continue;

	//	auto toOther = enemy->GetPosition() - (*it)->GetPosition();

	//	if(toOther.Length() > MinEnemyAvoidDistance) continue;

	//	enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
	//}
}

void EnemyIdleState::OnExit(Enemy* enemy)
{
}

EnemyIdleState::EnemyIdleState(const std::string& name)
{
	m_name = name;
}