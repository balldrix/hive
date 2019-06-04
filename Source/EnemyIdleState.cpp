#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "Randomiser.h"

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

	// stop movement
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyIdleState::Execute(Enemy* enemy)
{
	// true if timer is greater than thinking time with random adjustment
	if(enemy->GetTimer() > ThinkingTime * Randomiser::GetRandNum(0.4, 1.0))
	{
		// true if enemy is outside fighting range
		if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > FightingRange)
		{
			// radomise next action
			int randNum = Randomiser::GetRandNum(0, 1);
			if(randNum > 0)
			{
				enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
			}
			else
			{
				enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
			}

		}
		else if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > AttackRange)
		{
			// change to walking state
			enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
		}

		// reset timer
		enemy->ResetTimer();
	}
}

	void EnemyIdleState::OnExit(Enemy * enemy)
	{
	}

	EnemyIdleState::EnemyIdleState(std::string name)
	{
		m_name = name;
	}