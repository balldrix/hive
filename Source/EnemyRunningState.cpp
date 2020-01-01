#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "UnitVectors.h"

EnemyRunningState* EnemyRunningState::Instance()
{
	static EnemyRunningState instance("Running");
	return &instance;
}

void EnemyRunningState::OnEnter(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
	enemy->GetAnimator()->SetAnimation(m_name);
	enemy->GetHitBoxManager()->SetCurrentHitBox(m_name);

	enemy->SetMovementSpeed(enemy->GetData().objectData.m_runningSpeed);

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

void EnemyRunningState::Execute(Enemy* enemy)
{
}

void EnemyRunningState::OnExit(Enemy* enemy)
{
	enemy->GetAnimator()->Reset();
}

EnemyRunningState::EnemyRunningState(std::string name)
{
	m_name = name;
}
