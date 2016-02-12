#include "Enemy.h"
#include "Resources.h"
#include "UnitVectors.h"

Enemy::Enemy() :
m_ID(""),
m_enemyState(ENEMY_STATE_ROAM),
m_aiTimer(0.0f)
{
}

Enemy::~Enemy()
{
}

void 
Enemy::Init(Graphics* graphics, TextureManager* texture)
{
//	GameObject::Init();

//	m_pEnemySprite = sprite;
	
	m_aiTimer = AI_THINKING_TIME;
	
	SetRandomDirection();
}

void 
Enemy::Update(float deltaTime)
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

//	GameObject::Update(deltaTime);
	
//	m_pEnemySprite->Update(deltaTime);
	
//	FlipSprite(m_pEnemySprite, m_facingDirection);

	if (m_aiTimer < 0)
	{
		m_aiTimer = AI_THINKING_TIME;
	}

	if (m_position.x < TILE_SIZE || m_position.x + TILE_SIZE > GAME_WIDTH
		|| m_position.y < TILE_SIZE || m_position.y + TILE_SIZE > GAME_HEIGHT)
	{
		SetRandomDirection();
		//SetTargetVelocity(Vector2D(m_currentVelocity.x *-1, m_currentVelocity.y *-1));
	}

	m_aiTimer -= deltaTime;
	
}

void
Enemy::Render()
{
//	m_pEnemySprite->Render(D3DXVECTOR2(m_position.x, m_position.y));

	if(m_showHitBox)
	{
	//	DrawHitBox(m_pEnemySprite, m_collisionBox);
	}
}

Enemy::ENEMY_STATE
Enemy::Idle()
{
	return m_enemyState;
}

Enemy::ENEMY_STATE
Enemy::Roam()
{
	m_targetMovementSpeed = ENEMY_RUN_SPEED;
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
	m_targetVelocity = Vector2D().Zero();
	//m_pEnemySprite->SetCurrentFrame(0);
//	m_pEnemySprite->SetLoop(false);
	return ENEMY_STATE_DEAD;
}

Enemy::ENEMY_STATE
Enemy::Dead()
{
//	m_pEnemySprite->SetAnimation(ENEMY_STATE_DEAD);
	return m_enemyState;
}

void
Enemy::Reset()
{
	//m_active = false;
	m_position = Vector2D(0.0f,0.0f);
	m_targetMovementSpeed = ENEMY_WALK_SPEED;
	SetEnemyState(ENEMY_STATE_ROAM);
}


void
Enemy::SetEnemyState(ENEMY_STATE state)
{
	m_enemyState = state;
//	m_pEnemySprite->SetAnimation(state);
}

//void Enemy::SetAIState(AI_STATE state)
//{
//	m_aiState = state;
//}

void Enemy::SetRandomDirection()
{
	// randomise direction of movement
	int direction = Randomiser::GetRandNum(0, 7);
	switch (direction)
	{
	case 0:
		SetTargetVelocity(directionNS::RIGHT);
		break;
	case 1:
		SetTargetVelocity(directionNS::DOWNRIGHT);
		break;
	case 2:
		SetTargetVelocity(directionNS::DOWN);
		break;
	case 3:
		SetTargetVelocity(directionNS::DOWNLEFT);
		break;
	case 4:
		SetTargetVelocity(directionNS::LEFT);
		break;
	case 5:
		SetTargetVelocity(directionNS::UPLEFT);
		break;
	case 6:
		SetTargetVelocity(directionNS::UP);
		break;
	case 7:
		SetTargetVelocity(directionNS::UPRIGHT);
		break;
	default:
		SetTargetVelocity(directionNS::RIGHT);
		break;
	}
}

