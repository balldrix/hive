#include "EnemyWalkingState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "HitBoxManager.h"
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
	
	enemy->SetMovementSpeed(enemy->GetData().objectData.walkSpeed);

	Vector2 direction = Vector2::Zero;
	Vector2 targetPosition = enemy->GetPlayerTarget()->GetPosition();
	Vector2 position = enemy->GetPosition();

	direction = targetPosition - position;
	direction.Normalize();

	enemy->SetVelocity(direction);
}

void EnemyWalkingState::Execute(Enemy* enemy)
{
	enemy->PlayWalkingSound();
	auto distance = (enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length();

	if(distance < enemy->GetData().attackRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}

	if(distance > enemy->GetData().hostileRange)
	{
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}
}

void EnemyWalkingState::OnExit(Enemy* enemy)
{
	enemy->StopWalkingSound();
}

EnemyWalkingState::EnemyWalkingState(const std::string &name)
{
	m_name = name;
}