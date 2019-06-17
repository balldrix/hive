#include "Enemy.h"
#include "Graphics.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"
#include "pch.h"
#include "UnitVectors.h"
#include "Randomiser.h"

#include "EnemyOwnedStates.h"

Enemy::Enemy() :
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_thinkingTimer(0.0f),
	m_isHostile(false)
{}

Enemy::~Enemy()
{
	if(m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}

	if(m_shadow)
	{
		delete m_shadow;
		m_shadow = nullptr;
	}

	if(m_animator)
	{
		delete m_animator;
		m_animator = nullptr;
	}

	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}
}

void Enemy::Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager)
{
	m_position = position;
	m_sprite = new SpriteSheet(*sprite);
	m_shadow = new Sprite(*shadow);
	m_animator = new Animator(*animator);
	m_animator->SetAnimation(0);
	m_hitBoxManager = new HitBoxManager(*hitBoxManager);
	m_hitBoxManager->SetCurrentHitBox(0);
	
	ObjectData data = m_enemyData.m_objectData;
	m_movementSpeed = data.m_walkSpeed;
	m_acceleration = data.m_acceleration;
	m_deceleration = data.m_deceleration;

	m_stateMachine = new StateMachine<Enemy>(this);
	m_stateMachine->Init(EnemyIdleState::Instance(), nullptr, EnemyGlobalState::Instance());

	m_health = 4;
}

void
Enemy::Update(float deltaTime)
{
	// update state machine
	m_stateMachine->Update();

	// update object
	GameObject::Update(deltaTime);

	m_thinkingTimer += deltaTime;
}

void
Enemy::Render(Graphics* graphics)
{
	// render shadow first
	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_sprite)
	{
		m_sprite->SetDepth(m_groundPosition.y / graphics->GetHeight());

		// render enemy sprite
		if(m_animator)
		{
			m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spriteSheetIndex);
		}
		else
		{
			m_sprite->Render(graphics, 0);
		}
	}

	// render hitbox
	//if(m_hitBoxManager)
	//{
	//	m_hitBoxManager->Render(graphics);
	//}
}

void
Enemy::Reset()
{
	// set enemy state back to Idle
	m_stateMachine->ChangeState(EnemyIdleState::Instance());

	// Set Position 
	// TODO set world position and screen position
	m_position = m_enemyData.m_objectData.m_startingPosition;
	m_grounded = true;
	m_movementSpeed = m_enemyData.m_objectData.m_walkSpeed;

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
	m_health = 4;
	m_thinkingTimer = 0.0f;
}

void Enemy::SetData(const EnemyData& data)
{
	m_enemyData = data;
}

void Enemy::SetPlayerTarget(Player* player)
{
	m_playerTarget = player;
}

void Enemy::SetHostile(bool isHostile)
{
	m_isHostile = isHostile;
}

void Enemy::ResetTimer()
{
	m_thinkingTimer = 0.0f;
}

void Enemy::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	// true if health has gone or damage is high
	if(m_health < 1 || amount > 15)
	{
		// set knockback state
		m_stateMachine->ChangeState(EnemyKnockbackState::Instance());

		Vector2 direction = Vector2::Zero;

		// calculate direction to knockback
		if(this->GetPositionX() < source->GetPositionX())
		{
			direction = UnitVectors::UpLeft;
		}
		else
		{
			direction = UnitVectors::UpRight;
		}

		// knockback Enemy with force
		Knockback(direction, 80.0f);

		// bounce 
		SetKnockbackCount(1);
	}
	else
	{
		m_stateMachine->ChangeState(EnemyHurtState::Instance());
	}
}

void Enemy::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

void Enemy::Attack()
{
	int randomNum = Randomiser::Instance()->GetRandNum(0, 2);
	switch(randomNum)
	{
	case 0:
		EnemyAttackState::Instance()->SetAttack("Attack 1");
		break;
	case 1:
		EnemyAttackState::Instance()->SetAttack("Attack 2");
		break;
	case 2:
		EnemyAttackState::Instance()->SetAttack("Attack 3");
		break;
	default:
		EnemyAttackState::Instance()->SetAttack("Attack 1");
		break;
	}

	m_stateMachine->ChangeState((EnemyAttackState::Instance()));
}
