#include "GameObject.h"
#include "Sprite.h"

GameObject::GameObject() :
	m_ID(L"GameObject"),
	m_position(0.0f, 0.0f),
	m_currentVelocity(0.0f, 0.0f),
	m_targetVelocity(0.0f, 0.0f),
	m_currentMovementSpeed(0.0f),
	m_targetMovementSpeed(0.0f),
	m_active(false)
{
}

GameObject::~GameObject()
{
}

void
GameObject::SetID(const wchar_t* string)
{
	m_ID = string;
}

void GameObject::Update(float deltaTime)
{
	float speed;
	speed = Lerp(m_targetMovementSpeed, m_currentMovementSpeed, deltaTime);

	SetCurrentMovementSpeed(speed);

	m_position += (m_currentVelocity * speed) * deltaTime;
}

float GameObject::Lerp(float target, float current, float deltaTime)
{
	float tempValue = target - current;
	float lerpAmt = deltaTime * LERP_SPEED;

	if (tempValue > lerpAmt)
	{
		return current + lerpAmt;
	}

	if (tempValue < -lerpAmt)
	{
		return current - lerpAmt;
	}

	return target;
}

void GameObject::SetPositionX(unsigned int x)
{
	m_position.x = x;
}

void GameObject::SetPositionY(unsigned int y)
{
	m_position.y = y;
}

void GameObject::SetPosition(unsigned int x, unsigned int y)
{
	m_position.x = x;
	m_position.y = y;
}

void GameObject::SetPosition(Vector2 position)
{
	m_position = position;
}

void GameObject::SetTargetMovementSpeed(unsigned int speed)
{
	m_targetMovementSpeed = speed;
}

void GameObject::SetCurrentMovementSpeed(unsigned int speed)
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

void 
GameObject::SetActive(bool active)
{
	m_active = active;
}
