#include "MookEnemyGlobalState.h"

#include "StateMachine.h"
#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "Player.h"
#include "UnitVectors.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "Randomiser.h"
#include "EnemyAttackRunState.h"
#include "GameplayConstants.h"

using namespace GameplayConstants;

MookRunningEnemyGlobalState* MookRunningEnemyGlobalState::Instance()
{
	static MookRunningEnemyGlobalState instance;
	return &instance;
}

void MookRunningEnemyGlobalState::OnEnter(Enemy* enemy)
{

}

void MookRunningEnemyGlobalState::Execute(Enemy* enemy)
{
	if(enemy->GetHealth() < 1)
	{
		return;
	}

	auto currentState = enemy->GetStateMachine()->GetCurrentState();
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if((currentState == EnemyWalkingState::Instance() ||
		currentState == EnemyRunningState::Instance()) &&
		distance > enemy->GetData().chargeRange)
	{
		if(enemy->GetTimer() < 0.0f)
		{
			//enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
			enemy->SetPosition(enemy->GetPositionX(), enemy->GetPlayerTarget()->GetGroundPosition().y + 1);
			enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.8f, 2.0f));
		}
	}

	if(distance < enemy->GetData().attackRange &&
		fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY()) < VerticalHitRange)
	{
		if(enemy->IsHostile() == false)
		{
			enemy->SetHostile(true);
		}
			
		auto playerPos = Vector2(enemy->GetPlayerTarget()->GetPositionX(), 0);
		auto enemyPos = Vector2(enemy->GetPositionX(), 0);
		Vector2 dirToPlayer = (playerPos - enemyPos);
		dirToPlayer.Normalize();
		auto facingDir = Vector2(enemy->GetFacingDirection());

		if(currentState == EnemyRunningState::Instance() &&
			(dirToPlayer == facingDir))
		{
			enemy->GetStateMachine()->ChangeState(EnemyAttackRunState::Instance());
			return;
		}

		/*if(currentState == EnemyWalkingState::Instance() &&
			(distance < enemy->GetData().attackRange))
			enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());*/
	}
	else
	{
		enemy->SetHostile(false);
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

void MookRunningEnemyGlobalState::OnExit(Enemy* enemy)
{
}