#include "KingMookEnemyGlobalState.h"

#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "KingMook.h"
#include "KingMookChargeState.h"
#include "StateMachine.h"
#include "Player.h"
#include "Randomiser.h"
#include "PlayerOwnedStates.h"

KingMookEnemyGlobalState* KingMookEnemyGlobalState::Instance()
{
	static KingMookEnemyGlobalState instance;
	return &instance;
}

void KingMookEnemyGlobalState::OnEnter(Enemy* enemy)
{
}

void KingMookEnemyGlobalState::Execute(Enemy* enemy)
{
	if(enemy->GetHealth() < 1)
		return;

	Vector2 toPlayerTarget = enemy->GetPlayerTarget()->GetPosition() - enemy->GetPosition();

	if(enemy->GetStateMachine()->GetCurrentState() != EnemyKnockbackState::Instance() &&
	   enemy->GetStateMachine()->GetCurrentState() != EnemyDeadState::Instance())
	{
		if(enemy->GetCurrentVelocity().x < 0 ||
		   toPlayerTarget.x < 0 && enemy->GetPlayerTarget()->GetStateMachine()->IsInState(*PlayerIdleState::Instance()) == true)
			enemy->FlipHorizontally(true);

		if(enemy->GetCurrentVelocity().x > 0 ||
		   toPlayerTarget.x > 0 && enemy->GetPlayerTarget()->GetStateMachine()->IsInState(*PlayerIdleState::Instance()) == true)	
			enemy->FlipHorizontally(false);
	}

	if(toPlayerTarget.Length() < enemy->GetData().fightingRange &&
	   enemy->GetStateMachine()->GetCurrentState() != KingMookChargeState::Instance() &&
	   enemy->GetPlayerTarget()->GetStateMachine()->IsInState(*PlayerDeadState::Instance()) == false)
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

	if(toPlayerTarget.Length() > enemy->GetData().fightingRange &&
	   toPlayerTarget.Length() < enemy->GetData().chargeRange)
	{
		int randNum = Randomiser::Instance()->GetRandNum(0, 1);
		float timer = enemy->GetTimer();
		float thinkingTime = enemy->GetData().thinkingTime * Randomiser::Instance()->GetRandNum(0.5f, 1.0f);
		if(randNum > 0 && timer > thinkingTime)
		{
			enemy->GetStateMachine()->ChangeState(KingMookChargeState::Instance());
			enemy->ResetTimer();
			return;
		}
	}

	if((enemy->GetStateMachine()->GetCurrentState() == EnemyWalkingState::Instance() ||
		enemy->GetStateMachine()->GetCurrentState() == EnemyRunningState::Instance()) &&
	   toPlayerTarget.Length() > enemy->GetData().fightingRange)
	{
		if(enemy->GetTimer() > enemy->GetData().thinkingTime * Randomiser::Instance()->GetRandNum(0.8f, 2.0f))
		{
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
			enemy->ResetTimer();	
		}
	}
}

void KingMookEnemyGlobalState::OnExit(Enemy* enemy)
{
}