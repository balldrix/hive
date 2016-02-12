#include "Transform.h"

Transform::Transform() :
m_position(0.0f,0.0f),
m_currentVelocity(0.0f,0.0f),
m_targetVelocity(0.0f,0.0f),
m_currentMovementSpeed(0.0f),
m_targetMovementSpeed(0.0f)
{}

Transform::~Transform()
{}

void
Transform::Update(float deltaTime)
{
	float speed;
	speed = Lerp(m_targetMovementSpeed, m_currentMovementSpeed, deltaTime);

	SetCurrentMovementSpeed(speed);

	m_position += (m_currentVelocity * speed) * deltaTime;
}

float
Transform::Lerp(float target, float current, float deltaTime)
{
	float tempValue = target - current;
	float lerpAmt = deltaTime * LERP_SPEED;

	if(tempValue > lerpAmt)
	{
		return current + lerpAmt;
	}

	if(tempValue < -lerpAmt)
	{
		return current - lerpAmt;
	}

	return target;
}

void			
Transform::SetPositionX(unsigned int x)
{
	m_position.x = x;
}

void				
Transform::SetPositionY(unsigned int y)
{
	m_position.y = y;
}

void
Transform::SetPosition(unsigned int x, unsigned int y)
{
	m_position.x = x;
	m_position.y = y;
}

void				
Transform::SetPosition(Vector2D position)
{
	m_position = position;
}

void						
Transform::SetTargetMovementSpeed(unsigned int speed)
{
	m_targetMovementSpeed = speed;
}

void						
Transform::SetCurrentMovementSpeed(unsigned int speed)
{
	m_currentMovementSpeed = speed;
}

void
Transform::SetCurrentVelocity(float x, float y)
{
	m_currentVelocity.x = x;
	m_currentVelocity.y = y;
}

void
Transform::SetCurrentVelocity(Vector2D velocity)
{
	m_currentVelocity = velocity;
}

void		
Transform::SetTargetVelocity(float x, float y)
{
	m_targetVelocity.x = x;
	m_targetVelocity.y = y;
}

void
Transform::SetTargetVelocity(Vector2D velocity)
{
	m_targetVelocity = velocity;
}

void
Transform::SetTargetVelocityX(float x)
{
	m_targetVelocity.x = x;
}

void
Transform::SetTargetVelocityY(float y)
{
	m_targetVelocity.y = y;
}

void
Transform::Reset()
{
	SetPosition(0, 0);
	SetCurrentVelocity(0.0f, 0.0f);
	SetTargetVelocity(0.0f, 0.0f);
	SetCurrentMovementSpeed(0.0f);
	SetTargetMovementSpeed(0.0f);
}