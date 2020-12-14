#include "KingMookEnemyGlobalState.h"

#include "KingMook.h"
#include "StateMachine.h"
#include "EnemyOwnedStates.h"
#include "Player.h"
#include "Randomiser.h"

KingMookEnemyGlobalState* KingMookEnemyGlobalState::Instance()
{
	static KingMookEnemyGlobalState instance;
	return &instance;
}

void KingMookEnemyGlobalState::OnEnter(Enemy* enemy)
{
	if(enemy->GetHealth() < 1)
		return;

	if((enemy->GetStateMachine()->GetCurrentState() == EnemyWalkingState::Instance() ||
		enemy->GetStateMachine()->GetCurrentState() == EnemyRunningState::Instance()) &&
	   (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().fightingRange)
	{
		if(enemy->GetTimer() > enemy->GetData().thinkingTime * Randomiser::Instance()->GetRandNum(0.8, 2.0))
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		}

		enemy->ResetTimer();
	}

	if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < enemy->GetData().fightingRange)
	{
		if(enemy->IsHostile() == false)
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
			enemy->SetHostile(true);
		}
	}
	else
	{
		enemy->SetHostile(false);
	}

	// true if the enemy is not knocked back or dead
	if(enemy->GetStateMachine()->GetCurrentState() != EnemyKnockbackState::Instance() &&
	   enemy->GetStateMachine()->GetCurrentState() != EnemyDeadState::Instance())
	{
		// true if moving to the left
		if(enemy->GetCurrentVelocity().x < 0)
		{
			enemy->FlipHorizontally(true);
		}

		// true if moving to the right
		if(enemy->GetCurrentVelocity().x > 0)
		{
			enemy->FlipHorizontally(false);
		}
	}
}

void KingMookEnemyGlobalState::Execute(Enemy* enemy)
{
}

void KingMookEnemyGlobalState::OnExit(Enemy* enemy)
{
}