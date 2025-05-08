#include "NormalEnemyGlobalState.h"

#include "Enemy.h"
#include "EnemyKnockbackState.h"
#include "EnemyRunningState.h"
#include "StateMachine.h"

NormalEnemyGlobalState* NormalEnemyGlobalState::Instance()
{
	static NormalEnemyGlobalState instance;
	return &instance;
}

void NormalEnemyGlobalState::OnEnter(Enemy* enemy)
{
}

void NormalEnemyGlobalState::Execute(Enemy* enemy)
{
	if(enemy->GetHealth() < 1)
	{
		return;
	}

	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();
	auto isInKnockbackState = enemy->GetStateMachine()->IsInState(*EnemyKnockbackState::Instance());

	// true if moving to the left
	if(enemy->GetCurrentVelocity().x < 0)
	{
		enemy->FlipHorizontally(!isInKnockbackState);
	}

	// true if moving to the right
	if(enemy->GetCurrentVelocity().x > 0)
	{
		enemy->FlipHorizontally(isInKnockbackState);
	}

	if(enemy->GetTimer() > 0 || enemy->GetHealth() < 0)
		return;

	if(distance > enemy->GetData().hostileRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
		enemy->ResetStateChangeTimer();
	}

	//if(currentState == EnemyFallingState::Instance() || currentState == EnemyLandingState::Instance()) return;

	//if(distance <= enemy->GetData().hostileRange)
	//{
	//	if(enemy->IsHostile() == false && !enemy->GetStateMachine()->IsInState(*EnemyIdleState::Instance()))
	//	{
	//		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	//	}

	//	if(NPCManager::Instance()->GetAttackingEnemy() == nullptr)
	//		NPCManager::Instance()->SetAttackingEnemy(enemy);
	//}
	//else
	//{
	//	if(NPCManager::Instance()->GetAttackingEnemy() == enemy)
	//		NPCManager::Instance()->SetAttackingEnemy(nullptr);
	//}
}

void NormalEnemyGlobalState::OnExit(Enemy* enemy)
{
}