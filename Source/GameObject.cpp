#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject() :
	m_ID(L"GameObject"),
	m_position(0.0f, 0.0f),
	m_currentVelocity(0.0f, 0.0f),
	m_targetVelocity(0.0f, 0.0f),
	m_currentMovementSpeed(0.0f),
	m_targetMovementSpeed(0.0f),
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
	float speed;
	float velocityX;
	float velocityY;

	// interpolate object's speed
	speed = Lerp(m_targetMovementSpeed, m_currentMovementSpeed, deltaTime);

	// interpolate objects velocity		
	velocityX = Lerp(m_targetVelocity.x, m_currentVelocity.x, deltaTime);
	velocityY = Lerp(m_targetVelocity.y, m_currentVelocity.y, deltaTime);

	SetCurrentMovementSpeed(speed);
	SetCurrentVelocity(velocityX, velocityY);

	m_position += (m_currentVelocity * m_currentMovementSpeed) * deltaTime;
}

float GameObject::Lerp(float target, float current, float deltaTime)
{
	float tempValue = target - current;
	float accelLerpAmt = deltaTime * m_acceleration;
	float decelLerpAmt = deltaTime * m_deceleration;

	if(abs(target) > abs(current))
	{
		if(tempValue > accelLerpAmt)
		{
			return current + accelLerpAmt;
		}

		if(tempValue < -accelLerpAmt)
		{
			return current - accelLerpAmt;
		}
	}
	else if(abs(target) < abs(current))
	{
		if(tempValue > decelLerpAmt)
		{
			return current + decelLerpAmt;
		}

		if(tempValue < -decelLerpAmt)
		{
			return current - decelLerpAmt;
		}
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

void GameObject::SetTargetMovementSpeed(float speed)
{
	m_targetMovementSpeed = speed;
}

void GameObject::SetCurrentMovementSpeed(float speed)
{
	m_currentMovementSpeed = speed;
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
