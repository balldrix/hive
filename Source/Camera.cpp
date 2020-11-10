#include "Camera.h"
#include "GameObject.h"

Camera::Camera() :
	m_trackingTarget(nullptr),
	m_position(Vector2::Zero),
	m_origin(Vector2::Zero),
	m_width(0),
	m_height(0),
	m_maxWidth(0)
{
}

Camera::~Camera()
{
}

void Camera::Init(unsigned int width, unsigned int height, unsigned int worldWidth)
{
	m_width = width;
	m_height = height;
	m_origin = Vector2((float)width / 2, (float)height / 2);
	m_position = Vector2::Zero;
	m_maxWidth = worldWidth - width / 2;
}

void Camera::Update(float deltaTime)
{
	if(m_trackingTarget == nullptr)
		return;

	float x = m_trackingTarget->GetPositionX();
	if(x > m_width / 2 && x < m_maxWidth)
	{
		Vector2 position = m_position;
		position += (m_trackingTarget->GetCurrentVelocity() * m_trackingTarget->GetMovementSpeed()) * deltaTime;
		position.y = 0.0f;
		SetPosition(position);
	}
}

void Camera::SetTarget(GameObject* target)
{
	m_trackingTarget = target;
}

void Camera::SetPosition(const Vector2& position)
{
	m_position = position;
}

void Camera::SetWidth(unsigned int width)
{
	m_width = width;
}

void Camera::SetHeight(unsigned int height)
{
	m_height = height;
}

void Camera::Reset()
{
	m_position = Vector2::Zero;
}
