#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject() :
	m_ID(L"GameObject"),
	m_position(0.0f, 0.0f),
	m_currentVelocity(0.0f, 0.0f),
	m_targetVelocity(0.0f, 0.0f),
	m_movementSpeed(0.0f),
	m_acceleration(0.0f),
	m_deceleration(0.0f),
	m_active(false)
{
}

GameObject::~GameObject()
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
