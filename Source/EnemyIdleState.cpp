#include "EnemyIdleState.h"

#include "StateMachine.h"
#include "PlayerOwnedStates.h"
#include "Enemy.h"
#include "EnemyOwnedStates.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "Randomiser.h"
#include "GameplayConstants.h"

using namespace GameplayConstants;

EnemyIdleState* EnemyIdleState::Instance()
{
	static EnemyIdleState instance("idle");
	return &instance;
}

void EnemyIdleState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
	enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4, 1.0));
	enemy->SetTargetVelocity(Vector2::Zero);
}

void EnemyIdleState::Execute(Enemy* enemy)
{
	auto verticalDistance = fabs(enemy->GetPositionY() - enemy->GetPlayerTarget()->GetPositionY());
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(enemy->GetCurrentVelocity().LengthSquared() < 0.01f)
	{
		if(enemy->GetPlayerTarget()->GetPositionX() < enemy->GetPositionX())
			enemy->FlipHorizontally(true);
		else
			enemy->FlipHorizontally(false);
	}

	if(enemy->GetPlayerTarget()->GetKnockbackCount() < 1 && enemy->GetPlayerTarget()->GetHealth() < 1)
		enemy->GetStateMachine()->ChangeState(EnemyVictoryState::Instance());

	if(enemy->GetTimer() > 0 ||
		enemy->GetHealth() < 0)
		return;

	if((enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
		enemy->GetPlayerTarget()->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance()))
	{
		// true if enemy is outside hostile range
		if(distance > enemy->GetData().hostileRange)
		{
			enemy->GetStateMachine()->ChangeState(EnemyRunningState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4, 1.0));
		}
		else if(distance > enemy->GetData().attackRange)
		{
			enemy->GetStateMachine()->ChangeState(EnemyWalkingState::Instance());
			enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4, 1.0));
		}			
	}

	if(enemy->IsHostile() == false)
		return;

	if(distance < enemy->GetData().attackRange &&
		verticalDistance < VerticalHitRange)
	{
		double randnum = Randomiser::Instance()->GetRandNum(0.02, 1.8);
	
		enemy->Stop();
		enemy->ResetTimer(randnum);
		enemy->Attack();

		return;
	}
}

void EnemyIdleState::OnExit(Enemy* enemy)
{
}

EnemyIdleState::EnemyIdleState(const std::string &name)
{
	m_name = name;
}