#include "GameObject.h"
#include "SpriteSheet.h"
#include "HitBoxManager.h"
#include "Animator.h"
#include "ControlSystem.h"
#include "Camera.h"
#include "Constants.h"

using namespace GlobalConstants;

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
	m_sprite(nullptr),
	m_animator(nullptr),
	m_shadow(nullptr),
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

void GameObject::Init(const Vector2& position, Sprite* sprite)
{
}

void GameObject::Init(const Vector2& position, Sprite* sprite, Sprite* shadow)
{
}

void GameObject::Init(const Vector2& position, Spritesheet* sprite, Animator* animator, HitBoxManager* hitBoxManager)
{
}

void GameObject::Init(const Vector2& position, Spritesheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager)
{
}

void GameObject::Init(const Vector2& position, Spritesheet* sprite, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
}

void GameObject::Init(const Vector2& position, Spritesheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
}

void GameObject::SetCamera(Camera* cam)
{
	m_camera = cam;
}

void GameObject::SetID(std::string id)
{
	m_id = id;
}

void GameObject::Update(float deltaTime)
{
	// true if object is grounded
	if(m_grounded)
	{
		// ground y position
		m_groundPosition.y = m_position.y;
	}
	else
	{
		// apply gravity
		SetVelocity(m_currentVelocity.x, m_currentVelocity.y += Gravity * deltaTime);

		// true if the y position is close enough to the ground 
		if(std::abs(m_position.y - m_groundPosition.y) < 2.0f && m_currentVelocity.y > 0.0f)
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

	m_position += (m_currentVelocity * m_movementSpeed) * deltaTime;
	
	// update ground x position
	m_groundPosition.x = m_position.x;

	if(m_animator != nullptr)
		m_animator->Update(deltaTime);

	Vector2 screenPosition = m_position;
	
	if(m_camera != nullptr)
		screenPosition.x -= m_camera->GetPosition().x;

	Vector2 screenGroundPosition = m_groundPosition;
	
	if(m_camera != nullptr)
		screenGroundPosition.x -= m_camera->GetPosition().x;

	if(m_sprite != nullptr)
		m_sprite->SetPosition(screenPosition);

	if(m_shadow != nullptr)
		m_shadow->SetPosition(screenGroundPosition);

	if(m_hitBoxManager != nullptr)
		m_hitBoxManager->Update();
}

void GameObject::Move(const Vector2 &direction)
{
}

void GameObject::Stop()
{
	SetVelocity(Vector2::Zero);
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

bool GameObject::LoadDamageData(std::string filename)
{
	std::ifstream file;
	file.open(filename);

	if(file)
	{
		std::string line;
		m_damageData.clear();

		while(std::getline(file, line))
		{
			if(line[0] != '#')
			{
				std::string attackName = "";
				std::string value = "";

				file >> attackName;
				file >> value;
				m_damageData[attackName] = std::stoi(value);
			}
		}
	}
	else
	{
		return false;
	}

	file.close();
	return true;
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

int GameObject::GetDamage() const
{
	return 0;
}
