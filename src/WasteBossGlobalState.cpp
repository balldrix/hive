#include "WasteBossGlobalState.h"

#include "Enemy.h"
#include "EnemyDeadState.h"

WasteBossGlobalState* WasteBossGlobalState::Instance()
{
	static WasteBossGlobalState instance;
	return &instance;
}

void WasteBossGlobalState::OnEnter(Enemy* boss)
{
}

void WasteBossGlobalState::Execute(Enemy* boss)
{
	if(boss->GetHealth() < 1) return;

	// true if the enemy is not knocked back or dead
	auto currentState = boss->GetStateMachine()->GetCurrentState();
	if(currentState != EnemyDeadState::Instance())
	{
		// true if moving to the left
		if(boss->GetCurrentVelocity().x < 0)
		{
			boss->FlipHorizontally(true);
		}

		// true if moving to the right
		if(boss->GetCurrentVelocity().x > 0)
		{
			boss->FlipHorizontally(false);
		}
	}
}

void WasteBossGlobalState::OnExit(Enemy* boss)
{
}
