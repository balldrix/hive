#include "RunningEnemy.h"

#include "Enemy.h"
#include "GameObject.h"
#include "RunningEnemyDeadState.h"
#include "StateMachine.h"

RunningEnemy::RunningEnemy()
{
}

void RunningEnemy::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	if(m_health < 1)
	{
		m_stateMachine->ChangeState(RunningEnemyDeadState::Instance());
	}

	PlayHurtSound();
}

void RunningEnemy::Reset()
{
	Enemy::Reset();

	m_movementSpeed = m_enemyDefinition.runningSpeed;
}
