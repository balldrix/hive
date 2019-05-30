#include "Enemy.h"
#include "Graphics.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"
#include "pch.h"

#include "EnemyOwnedStates.h"

Enemy::Enemy() :
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_thinkingTimer(0.0f)
{}

Enemy::~Enemy()
{
	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}
}

void Enemy::Init(const Vector2 &position, SpriteSheet *sprite, Sprite *shadow, Animator *animator, HitBoxManager *hitBoxManager)
{
	m_sprite = sprite;
	m_shadow = shadow;
	m_position = position;
	m_acceleration = 1.0f;
	m_deceleration = 1.25f;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;
	m_hitBoxManager->SetCurrentHitBox(0);
	m_movementSpeed = EnemyWalkSpeed;
	m_acceleration = EnemyAcceleration;
	m_deceleration = EnemyDeceleration;

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
Enemy::Render(Graphics *graphics)
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
	SetPosition(EnemyStartScreenPositionX, EnemyStartScreenPositionY);

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
}

void Enemy::SetPlayerTarget(Player* player)
{
	m_playerTarget = player;
}

void Enemy::ApplyDamage(GameObject* source, const int &amount)
{
	m_health -= amount;

	// true if health has gone or damage is high
	if(m_health < 1 || amount > 15)
	{
		// set knockback state
		m_stateMachine->ChangeState(EnemyKnockbackState::Instance());

		// calculate direction to knockback
		Vector2 direction = Vector2(this->GetPosition().x - source->GetPosition().x, 0.0f) - Vector2(0.0f, 10.0f);
		direction.Normalize();

		// knockback Enemy with 80.0f force
		Knockback(direction, 90.0f);

		// bounce 
		SetKnockbackCount(1);
	}
	else
	{
		m_stateMachine->ChangeState(EnemyHurtState::Instance());
	}
}

void Enemy::Knockback(const Vector2& direction, const float &force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}
