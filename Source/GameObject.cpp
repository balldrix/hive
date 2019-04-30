#include "GameObject.h"
#include "SpriteSheet.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"

GameObject::GameObject() :
	m_ID(L"GameObject"),
	m_position(0.0f, 0.0f),
	m_currentVelocity(0.0f, 0.0f),
	m_targetVelocity(0.0f, 0.0f),
	m_movementSpeed(0.0f),
	m_acceleration(0.0f),
	m_deceleration(0.0f),
	m_sprite(nullptr),
	m_animator(nullptr),
	m_shadow(nullptr),
	m_hitBoxManager(nullptr),
	m_controlSystem(nullptr),
	m_active(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init(const Vector2& position, Sprite* sprite)
{
}

void GameObject::Init(const Vector2& position, Sprite* sprite, Sprite* shadow)
{
}

void GameObject::Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager)
{
}

void GameObject::Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager)
{
}

void GameObject::Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
}

void GameObject::Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
}

void GameObject::SetID(const wchar_t* string)
{
	m_ID = string;
}

void GameObject::Update(float deltaTime)
{
	float t;
	float x; 
	t = GetLerpAmount(m_targetVelocity.x);
	x = Lerp(m_targetVelocity.x, m_currentVelocity.x, t * deltaTime);
	m_currentVelocity.x = x;

	float y;
	t = GetLerpAmount(m_targetVelocity.y);
	y = Lerp(m_targetVelocity.y, m_currentVelocity.y, t * deltaTime);
	m_currentVelocity.y = y;

	m_position += (m_currentVelocity * m_movementSpeed) * deltaTime;

	// if object has an animator
	if(m_animator)
	{
		// update animator
		m_animator->Update(deltaTime);
	}

	// update position of sprite
	if(m_sprite)
	{
		m_sprite->SetPosition(m_position);
	}

	// update shadow position
	if(m_shadow)
	{
		m_shadow->SetPosition(m_position);
	}

	// update hitbox
	if(m_hitBoxManager)
	{
		m_hitBoxManager->Update();
	}
}

void GameObject::Move(const Vector2 &direction)
{
}

void GameObject::Stop()
{
}

float GameObject::GetLerpAmount(float num)
{
	if(num == 0.0f)
	{
		return m_deceleration;
	}
	else
	{
		return m_acceleration;
	}
}

float GameObject::Lerp(float target, float current, float amount)
{
	float tempValue = target - current;

	if(tempValue > amount)
	{
		return current + amount;
	}

	if(tempValue < -amount)
	{
		return current - amount;
	}

	return target;
}

void GameObject::FlipHorizontally(bool flip)
{
	// true if flip param is true
	if(flip == true)
	{
		// flip sprite
		m_sprite->SetFlipEffect(SpriteEffects::SpriteEffects_FlipHorizontally);

	}
	else
	{
		m_sprite->SetFlipEffect(SpriteEffects::SpriteEffects_None);
	}

	// flip hitboxes
	m_hitBoxManager->SetFlipped(flip);
}

void GameObject::SetPositionX(unsigned int x)
{
	m_position.x = (float)x;
}

void GameObject::SetPositionY(unsigned int y)
{
	m_position.y = (float)y;
}

void GameObject::SetPosition(unsigned int x, unsigned int y)
{
	m_position.x = (float)x;
	m_position.y = (float)y;
}

void GameObject::SetPosition(Vector2 position)
{
	m_position = position;
}

void GameObject::SetMovementSpeed(float speed)
{
	m_movementSpeed = speed;
}

void GameObject::SetCurrentVelocity(float x, float y)
{
	m_currentVelocity.x = x;
	m_currentVelocity.y = y;
}

void GameObject::SetCurrentVelocity(Vector2 velocity)
{
	m_currentVelocity = velocity;
}

void GameObject::SetTargetVelocity(float x, float y)
{
	m_targetVelocity.x = x;
	m_targetVelocity.y = y;
}

void GameObject::SetTargetVelocity(Vector2 velocity)
{
	m_targetVelocity = velocity;
}

void GameObject::SetTargetVelocityX(float x)
{
	m_targetVelocity.x = x;
}

void GameObject::SetTargetVelocityY(float y)
{
	m_targetVelocity.y = y;
}

void GameObject::SetAcceleration(float accel)
{
	m_acceleration = accel;
}

void GameObject::SetActive(bool active)
{
	m_active = active;
}

void GameObject::ApplyDamage(int amount)
{
}
