#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "UnitVectors.h"

EnemyWalkingState* EnemyWalkingState::Instance()
{
	static EnemyWalkingState instance("Walking");
	return &instance;
}

void EnemyWalkingState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);
	
	enemy->SetMovementSpeed(enemy->GetData().m_objectData.m_walkSpeed);

	Vector2 direction = Vector2::Zero;
	Vector2 targetPosition = enemy->GetPlayerTarget()->GetPosition();
	Vector2 position = enemy->GetPosition();

	direction = targetPosition - position;
	direction.Normalize();

	enemy->SetVelocity(direction);
}

void EnemyWalkingState::Execute(Enemy* enemy)
{
	if((enemy->GetPosition() - enemy->GetPlayerTarget()->GetPosition()).Length() < enemy->GetData().m_attackRange)
	{
		// change to idle state
		enemy->GetStateMachine()->ChangeState(EnemyIdleState::Instance());
	}
}

void EnemyWalkingState::OnExit(Enemy* enemy)
{
}

EnemyWalkingState::EnemyWalkingState(std::string name)
{
	m_name = name;
}