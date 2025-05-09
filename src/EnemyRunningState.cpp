#include "EnemyRunningState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

EnemyRunningState* EnemyRunningState::Instance()
{
	static EnemyRunningState instance("run");
	return &instance;
}

void EnemyRunningState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->SetMovementSpeed(enemy->GetData().runningSpeed);

	//if(enemy->GetStateMachine()->GetPreviousState() == EnemyAttackRunState::Instance())
		//return;

	//Vector2 direction = Vector2::Zero;
	//float targetXPosition = enemy->GetPlayerTarget()->GetPositionX();
	//float xPosition = enemy->GetPositionX();

	//if(targetXPosition < xPosition)
	//{
	//	direction = UnitVectors::Left;
	//}

	//if(targetXPosition > xPosition)
	//{
	//	direction = UnitVectors::Right;
	//}

	//enemy->SetTargetVelocity(direction);
}

void EnemyRunningState::Execute(Enemy* enemy)
{
	enemy->ProcessSteering();
	enemy->PlayFootstepSound();

	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(distance < enemy->GetData().hostileRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
		enemy->ResetStateChangeTimer();
	}
}

void EnemyRunningState::OnExit(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->StopWalkingSound();
}

EnemyRunningState::EnemyRunningState(const std::string &name)
{
	m_name = name;
}
