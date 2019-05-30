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

}

void EnemyGlobalState::OnExit(Enemy* enemy)
{
}