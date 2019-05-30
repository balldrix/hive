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
	
	enemy->SetMovementSpeed(EnemyWalkSpeed);
}

void EnemyWalkingState::Execute(Enemy* enemy)
{
	Vector2 direction = Vector2::Zero;
	float targetXPosition = enemy->GetPlayerTarget()->GetPositionX();
	float xPosition = enemy->GetPositionX();

	if(targetXPosition < xPosition)
	{
		direction = UnitVectors::Left;
	}

	if(targetXPosition > xPosition)
	{
		direction = UnitVectors::Right;
	}

	enemy->SetTargetVelocity(direction);
}

void EnemyWalkingState::OnExit(Enemy* enemy)
{
}

EnemyWalkingState::EnemyWalkingState(std::string name)
{
	m_name = name;
}