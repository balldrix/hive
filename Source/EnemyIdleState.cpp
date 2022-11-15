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
	static EnemyIdleState instance("Idle");
	return &instance;
}

void EnemyIdleState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
	enemy->ResetTimer();
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyIdleState::Execute(Enemy* enemy)
{
	if(enemy->GetPlayerTarget()->GetKnockbackCount() < 1 && enemy->GetPlayerTarget()->GetHealth() < 1)
		enemy->GetStateMachine()->ChangeState(EnemyVictoryState::Instance());

	if(enemy->GetTimer() > enemy->GetData().thinkingTime * Randomiser::Instance()->GetRandNum(0.4, 1.0) &&
	   enemy->GetHealth() > 0 &&
	   (enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
		enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance()))
	{
		// true if enemy is outside fighting range
		if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().fightingRange)
		{
			// radomise next action
			int randNum = Randomiser::Instance()->GetRandNum(0, 1);
			if(randNum > 0)
			{
				enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
			}
			else
			{
				enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
			}

		}
		else if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().attackRange &&
				(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY()) < 5.0f)
		{
			// change to walking state
			enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
		}

		// reset timer
		enemy->ResetTimer();
	}

	if(enemy->IsHostile() == false)
		return;

	if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < enemy->GetData().attackRange &&
		fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY()) < VerticalHitRange)
	{
		double randnum = Randomiser::Instance()->GetRandNum(0.02, 1.8);
		double time = randnum * enemy->GetData().thinkingTime;
		float timer = enemy->GetTimer();
		if(timer > time)
		{
			enemy->Stop();

			// reset timer
			enemy->ResetTimer();
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