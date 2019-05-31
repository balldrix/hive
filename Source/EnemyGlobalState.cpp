#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"
#include "UnitVectors.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "Randomiser.h"

EnemyGlobalState* EnemyGlobalState::Instance()
{
	static EnemyGlobalState instance;
	return &instance;
}

void EnemyGlobalState::OnEnter(Enemy* enemy)
{

}

void EnemyGlobalState::Execute(Enemy* enemy)
{
	if(enemy->GetStateMachine()->GetCurrentState() == EnemyWalkingState::Instance() ||
		enemy->GetStateMachine()->GetCurrentState() == EnemyRunningState::Instance())
	{
		if(enemy->GetTimer() > ThinkingTime * Randomiser::GetRandNum(0.8, 2.0))
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		}

		if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < 16)
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		}
	}

	// true if the enemy is not knocked back
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

void EnemyGlobalState::OnExit(Enemy* enemy)
{
}