#include "EnemyIdleState.h"

#include "StateMachine.h"
#include "PlayerOwnedStates.h"
#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "Randomiser.h"
#include "GameplayConstants.h"

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
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
	enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyIdleState::Execute(Enemy* enemy)
{
	if(enemy->GetCurrentVelocity().LengthSquared() < 0.01f)
	{
		if(enemy->GetPlayerTarget()->GetPositionX() < enemy->GetPositionX())
			enemy->FlipHorizontally(true);
		else
			enemy->FlipHorizontally(false);
	}

	if(enemy->GetPlayerTarget()->GetKnockbackCount() < 1 && enemy->GetPlayerTarget()->GetHealth() < 1)
		enemy->GetStateMachine()->ChangeState(EnemyVictoryState::Instance());

	if(enemy->GetTimer() < 0 &&
	   enemy->GetHealth() > 0 &&
	   (enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
		enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance()))
	{
		// true if enemy is outside fighting range
		if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().fightingRange)
		{
			enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
		}
		else if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().attackRange &&
				(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY()) < enemy->GetData().fightingRange)
		{
			enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
		}		
	}

	if(enemy->IsHostile() == false)
		return;

	if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < enemy->GetData().attackRange &&
		fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY()) < VerticalHitRange)
	{
		float randnum = Randomiser::Instance()->GetRandNum(0.02f, 1.8f);
	
		if(enemy->GetTimer() < 0)
		{
			enemy->Stop();

			enemy->ResetTimer(randnum);
			enemy->Attack();
		}
		return;
	}
}

void EnemyIdleState::OnExit(Enemy* enemy)
{
}

EnemyIdleState::EnemyIdleState(const std::string &name)
{
	m_name = name;
}