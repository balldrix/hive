#include "EnemyOwnedStates.h"

#include "KingMook.h"
#include "StateMachine.h"
#include "Player.h"
#include "Randomiser.h"

KingMookEnemyGlobalState* KingMookEnemyGlobalState::Instance()
{
	static KingMookEnemyGlobalState instance;
	return &instance;
}

KingMookEnemyGlobalState::KingMookEnemyGlobalState(std::string name)
{
	m_name = name;
}

void KingMookEnemyGlobalState::OnEnter(Enemy* enemy)
{
}

void KingMookEnemyGlobalState::Execute(Enemy* enemy)
{
	if(enemy->GetHealth() < 1)
		return;

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

	if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < enemy->GetData().fightingRange &&
	   enemy->GetStateMachine()->GetCurrentState() != KingMookChargeState::Instance())
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

	if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().fightingRange &&
	   (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < enemy->GetData().chargeRange)
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
	   (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() > enemy->GetData().fightingRange)
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