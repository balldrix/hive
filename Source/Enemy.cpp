#include "Enemy.h"
#include "Resources.h"
#include "UnitVectors.h"

Enemy::Enemy() :
m_graphics(NULL),
m_enemyTexture(NULL),
m_ID(""),
m_enemyState(ENEMY_STATE_IDLE),
m_aiTimer(0.0f),
m_active(false)
{
}

Enemy::~Enemy()
{
}

void 
Enemy::Init(Graphics* graphics, Texture* enemyTexture)
{
	m_graphics = graphics;
	m_enemyTexture = enemyTexture;
	
	SetEnemyState(ENEMY_STATE_IDLE);
	m_aiTimer = AI_THINKING_TIME;
}

void 
Enemy::Update(float deltaTime)
{
	if(m_active)
	{
		if(m_aiTimer < 0)
		{
			switch(m_enemyState)
			{
				case ENEMY_STATE_IDLE:
				{
					SetEnemyState(Idle());
					break;
				}
				case ENEMY_STATE_ROAM:
				{
					SetEnemyState(Roam());
					break;
				}
				case ENEMY_STATE_ATTACKING:
				{
					SetEnemyState(Attack());
					break;
				}
				case ENEMY_STATE_DEATH:
				{
					SetEnemyState(Die());
					break;
				}
				case ENEMY_STATE_DEAD:
				{
					SetEnemyState(Dead());
					break;
				}
			}
			
			m_aiTimer = AI_THINKING_TIME;
		}

		m_aiTimer -= deltaTime;

	}
}

void
Enemy::Render()
{
	if(m_active)
	{
	}
}

void
Enemy::Reset()
{

}

Enemy::ENEMY_STATE
Enemy::Idle()
{
	return ENEMY_STATE_IDLE;
}

Enemy::ENEMY_STATE
Enemy::Roam()
{
	return m_enemyState;
}

Enemy::ENEMY_STATE
Enemy::Attack()
{
	return m_enemyState;
}

Enemy::ENEMY_STATE
Enemy::Die()
{
	return ENEMY_STATE_DEAD;
}

Enemy::ENEMY_STATE
Enemy::Dead()
{
	return m_enemyState;
}

void
Enemy::SetEnemyState(ENEMY_STATE state)
{
	m_enemyState = state;
}

void Enemy::SetRandomDirection()
{
	// randomise direction of movement
	int direction = Randomiser::GetRandNum(0, 7);
	switch (direction)
	{
	case 0:
		//SetTargetVelocity(UnitVectors::Right);
		break;
	case 1:
		//SetTargetVelocity(UnitVectors::DownRight);
		break;
	case 2:
		//SetTargetVelocity(UnitVectors::Down);
		break;
	case 3:
		//SetTargetVelocity(UnitVectors::DownLeft);
		break;
	case 4:
		//SetTargetVelocity(UnitVectors::Left);
		break;
	case 5:
		//SetTargetVelocity(UnitVectors::UpLeft);
		break;
	case 6:
		//SetTargetVelocity(UnitVectors::Up);
		break;
	case 7:
		//SetTargetVelocity(UnitVectors::UpRight);
		break;
	default:
		//SetTargetVelocity(UnitVectors::Right);
		break;
	}
}

void
Enemy::SetActive(bool active)
{
	m_active = active;
}