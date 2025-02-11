#include "MookEnemyGlobalState.h"

#include "Enemy.h"
#include "EnemyDeadState.h"
#include "EnemyIdleState.h"
#include "EnemyKnockbackState.h"
#include "NPCManager.h"
#include "StateMachine.h"

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

	auto currentState = enemy->GetStateMachine()->GetCurrentState();
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(distance <= enemy->GetData().hostileRange)
	{
		if (enemy->IsHostile() == false)
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
			enemy->SetHostile(true);
		}

		if(NPCManager::Instance()->GetAttackingEnemy() == nullptr)
			NPCManager::Instance()->SetAttackingEnemy(enemy);
	}
	else
	{
		enemy->SetHostile(false);

		if(NPCManager::Instance()->GetAttackingEnemy() == enemy)
			NPCManager::Instance()->SetAttackingEnemy(nullptr);
	}

	// true if the enemy is not knocked back or dead
	if(currentState != EnemyKnockbackState::Instance() &&
		currentState != EnemyDeadState::Instance())
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