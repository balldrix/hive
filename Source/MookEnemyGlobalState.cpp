#include "MookEnemyGlobalState.h"

#include "StateMachine.h"
#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "Player.h"
#include "UnitVectors.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "Randomiser.h"

MookEnemyGlobalState* MookEnemyGlobalState::Instance()
{
	static MookEnemyGlobalState instance;
	return &instance;
}

void MookEnemyGlobalState::OnEnter(Enemy* enemy)
{

}

void MookEnemyGlobalState::Execute(Enemy* enemy)
{
	if(enemy->GetHealth() < 1)
	{
		return;
	}

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

void MookEnemyGlobalState::OnExit(Enemy* enemy)
{
}