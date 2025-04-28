#include "GameObject.h"

#include "Animator.h"
#include "Camera.h"
#include "Collider.h"
#include "DamageData.h"
#include "GameplayConstants.h"
#include "HitBoxManager.h"
#include "LevelCollision.h"
#include "SpriteFx.h"

#include <directxtk/SimpleMath.h>
#include <directxtk/SpriteBatch.h>
#include <fstream>
#include <iosfwd>
#include <string>

using namespace DirectX::SimpleMath;
using namespace GameplayConstants;

GameObject::GameObject() :
	m_id("GameObject"),
	m_camera(nullptr),
	m_position(0.0f, 0.0f),
	m_groundPosition(0.0f, 0.0f),
	m_currentVelocity(0.0f, 0.0f),
	m_targetVelocity(0.0f, 0.0f),
	m_movementSpeed(0.0f),
	m_acceleration(0.0f),
	m_deceleration(0.0f),
	m_facingDirection(Vector3::Right),
	m_spritesheet(nullptr),
	m_animator(nullptr),
	m_shadow(nullptr),
	m_dustFx(nullptr),
	m_hitBoxManager(nullptr),
	m_controlSystem(nullptr),
	m_health(0),
	m_knockbackCount(0),
	m_deathTimer(0.0f),
	m_grounded(true),
	m_dead(false),
	m_active(false)
{
}

GameObject::~GameObject()
{
	if(m_hitBoxManager)
	{
		delete m_hitBoxManager;
		m_hitBoxManager = nullptr;
	}
}

void GameObject::SetCamera(Camera* cam)
{
	m_camera = cam;
}

void GameObject::SetID(const std::string &id)
{
	m_id = id;
}

void GameObject::Update(float deltaTime)
{
	if(m_grounded)
	{
		m_groundPosition.y = m_position.y;
	}
	else
	{
		SetVelocity(m_currentVelocity.x, m_currentVelocity.y += Gravity * deltaTime);

		if(m_position.y > m_groundPosition.y && m_currentVelocity.y > 0.0f)
		{
			m_grounded = true;
			m_position.y = m_groundPosition.y;
			m_currentVelocity.y = 0.0f;
			m_targetVelocity.y = 0.0f;
		}
	}

	float t;
	float x;
	t = GetLerpAmount(m_targetVelocity.x);
	x = Lerp(m_targetVelocity.x, m_currentVelocity.x, t * deltaTime);
	m_currentVelocity.x = x;

	float y;
	t = GetLerpAmount(m_targetVelocity.y);
	y = Lerp(m_targetVelocity.y, m_currentVelocity.y, t * deltaTime);
	m_currentVelocity.y = y;

	Vector2 velocity = (m_currentVelocity * m_movementSpeed) * deltaTime;
	Vector2 newPosition = m_position + velocity;
	Collider pushBox = m_hitBoxManager->GetPushBox();

	if(velocity.x > 0 && LevelCollision::IsCollision(Vector2(newPosition.x + pushBox.GetWidth(), m_groundPosition.y)))
	{
		velocity.x = 0;
	}
	else if(velocity.x < 0 && LevelCollision::IsCollision(Vector2(newPosition.x - pushBox.GetWidth(), m_groundPosition.y)))
	{
		velocity.x = 0;
	}

	if(m_grounded)
	{
		if(velocity.y > 0 && LevelCollision::IsCollision(Vector2(m_groundPosition.x, newPosition.y + pushBox.GetHeight())))
		{
			velocity.y = 0;
		}
		else if(velocity.y < 0 && LevelCollision::IsCollision(Vector2(m_groundPosition.x, newPosition.y - pushBox.GetHeight())))
		{
			velocity.y = 0;
		}
	}

	m_position += velocity;
	m_currentVelocity = (velocity / m_movementSpeed) / deltaTime;
	m_groundPosition.x = m_position.x;

	if(m_animator != nullptr)
		m_animator->Update(deltaTime);

	Vector2 screenPosition = m_position;
	
	if(m_camera != nullptr)
		screenPosition -= m_camera->GetPosition();

	Vector2 screenGroundPosition = m_groundPosition;
	
	if(m_camera != nullptr)
		screenGroundPosition -= m_camera->GetPosition();

	if(m_spritesheet != nullptr)
		m_spritesheet->SetPosition(screenPosition);

	if(m_shadow != nullptr)
		m_shadow->SetPosition(screenGroundPosition);

	if(m_dustFx != nullptr)
		m_dustFx->Update(deltaTime);
}

void GameObject::Move(const Vector2 &direction)
{
}

void GameObject::Stop()
{
	SetVelocity(Vector2::Zero);
}

float GameObject::GetLerpAmount(const float& num) const
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
	auto facingDirection = Vector3::Right;
	auto spriteSheetEffects = SpriteEffects::SpriteEffects_None;

	if(flip == true)
	{
		facingDirection = Vector3::Left;
		spriteSheetEffects = SpriteEffects::SpriteEffects_FlipHorizontally;
	}	

	m_facingDirection = facingDirection;
	m_spritesheet->SetFlipEffect(spriteSheetEffects);
	m_hitBoxManager->SetFlipped(flip);

	if(m_shadow != nullptr)
		m_shadow->SetFlipEffect(spriteSheetEffects);
}

void GameObject::SetPositionX(float x)
{
	m_position.x = x;
}

void GameObject::SetPositionY(float y)
{
	m_position.y = y;
}

void GameObject::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void GameObject::SetPosition(const Vector2& position)
{
	m_position = position;
}

void GameObject::SetMovementSpeed(float speed)
{
	m_movementSpeed = speed;
}

// set velocity without lerping
void GameObject::SetVelocity(float x, float y)
{
	SetTargetVelocity(x, y);
	SetCurrentVelocity(x, y);
}

// set velocity without lerping
void GameObject::SetVelocity(const Vector2& velocity)
{
	SetTargetVelocity(velocity);
	SetCurrentVelocity(velocity);
}

void GameObject::SetCurrentVelocity(float x, float y)
{
	m_currentVelocity.x = x;
	m_currentVelocity.y = y;
}

void GameObject::SetCurrentVelocity(const Vector2& velocity)
{
	m_currentVelocity = velocity;
}

void GameObject::SetTargetVelocity(float x, float y)
{
	m_targetVelocity.x = x;
	m_targetVelocity.y = y;
}

void GameObject::SetTargetVelocity(const Vector2& velocity)
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

void GameObject::SetDeceleration(float decel)
{
	m_deceleration = decel;
}

void GameObject::SetHealth(int health)
{
	m_health = health;
}

void GameObject::SetGrounded(bool grounded)
{
	m_grounded = grounded;
}

void GameObject::SetActive(bool active)
{
	m_active = active;
}

void GameObject::SetKnockbackCount(int count)
{
	m_knockbackCount = count;
}

int GameObject::GetMaxHealth() const
{
	return 0;
}

void GameObject::ApplyDamage(GameObject* source, const int& amount)
{
}

void GameObject::Knockback(const Vector2& direction, const float& force)
{
}

void GameObject::DisplayDust(const Vector2& position)
{
	m_dustFx->DisplayFx(position);
}

DamageData GameObject::GetDamageData() const
{
	return DamageData();
}