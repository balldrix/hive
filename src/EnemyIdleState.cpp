#include "EnemyIdleState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyRunningState.h"
#include "EnemyWalkingState.h"
#include "GameplayConstants.h"
#include "HitBoxManager.h"
#include "NPCManager.h"
#include "Player.h"
#include "PlayerDeadState.h"
#include "PlayerKnockbackState.h"
#include "Randomiser.h"
#include "StateMachine.h"

#include "directxtk/SimpleMath.h"
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
	enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyIdleState::Execute(Enemy* enemy)
{
	auto verticalDistance = fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY());
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(enemy->GetCurrentVelocity().LengthSquared() < 0.01f)
	{
		if(enemy->GetPlayerTarget()->GetPositionX() < enemy->GetPositionX())
			enemy->FlipHorizontally(true);
		else
			enemy->FlipHorizontally(false);
	}

	if(enemy->GetPlayerTarget()->GetKnockbackCount() < 1 && enemy->GetPlayerTarget()->GetHealth() < 1)
		return;

	if((enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() == PlayerKnockbackState::Instance() ||
		enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() == PlayerDeadState::Instance())) return;

	//if(distance < enemy->GetData().fightRange)
	//{
	//	enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
	//}

	if(enemy->GetTimer() > 0 ||
		enemy->GetHealth() < 0)
		return;

	if((enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
		enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance()))
	{
		// true if enemy is outside hostile range
		if(distance > enemy->GetData().hostileRange)
		{
			enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
		}
		else if(distance > enemy->GetData().fightRange || (NPCManager::Instance()->GetAttackingEnemy() == enemy && distance > enemy->GetData().attackRange))
		{
			enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
		}
	}

	if(enemy->IsHostile() == false)
		return;

	auto enemies = enemy->GetManager()->GetEnemyList();

	if(distance < enemy->GetData().fightRange
		&& verticalDistance < VerticalHitRange
		&& NPCManager::Instance()->GetAttackingEnemy() == enemy)
	{
		double randnum = Randomiser::Instance()->GetRandNum(0.02, 1.8);
	
		enemy->Stop();
		enemy->ResetTimer((float)randnum);
		enemy->Attack();
		return;
	}

	for(auto it = enemies.begin(); it != enemies.end(); it++)
	{
		if(*it == enemy) continue;

		auto toOther = enemy->GetPosition() - (*it)->GetPosition();

		if(toOther.Length() > MinEnemyAvoidDistance) continue;

		enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
	}
}

void EnemyIdleState::OnExit(Enemy* enemy)
{
}

EnemyIdleState::EnemyIdleState(const std::string &name)
{
	m_name = name;
}