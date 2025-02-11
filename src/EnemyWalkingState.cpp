#include "EnemyWalkingState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
#include "Randomiser.h"
#include "StateMachine.h"

#include <directxtk/SimpleMath.h>
#include <string>

EnemyWalkingState* EnemyWalkingState::Instance()
{
	static EnemyWalkingState instance("walk");
	return &instance;
}

void EnemyWalkingState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
	enemy->SetMovementSpeed(enemy->GetData().objectData.walkSpeed);
}

void EnemyWalkingState::Execute(Enemy* enemy)
{
	enemy->ProcessSteering();
	enemy->PlayWalkingSound();

	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(enemy->GetTimer() > 0) return;

	if(distance < enemy->GetData().attackRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}

	if(distance > enemy->GetData().hostileRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}

	enemy->ResetTimer(Randomiser::Instance()->GetRandNum(0.4f, 1.0f));
}

void EnemyWalkingState::OnExit(Enemy* enemy)
{
	enemy->StopWalkingSound();
}

EnemyWalkingState::EnemyWalkingState(const std::string &name)
{
	m_name = name;
}