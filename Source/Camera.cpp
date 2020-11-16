#include "Camera.h"
#include "GameObject.h"

Camera::Camera() :
	m_trackingTarget(nullptr),
	m_position(Vector2::Zero),
	m_width(0),
	m_minBoundaryX(0),
	m_maxBoundaryX(0)
{
}

Camera::~Camera()
{
}

void Camera::Init(unsigned int width, unsigned int maxBoundary)
{
	m_width = width;
	m_minBoundaryX = (float)m_width / 2;
	m_maxBoundaryX = (float)maxBoundary;
	m_position = Vector2::Zero;
}

void Camera::Update(float deltaTime)
{
	if(m_trackingTarget == nullptr)
		return;

	float targetX = m_trackingTarget->GetPositionX();

	if(targetX < m_minBoundaryX)
		return;

	m_position.x += (m_trackingTarget->GetCurrentVelocity().x * m_trackingTarget->GetMovementSpeed()) * deltaTime;
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
	
void Camera::SetBoundary(float x)
{
	m_minBoundaryX = x;
}

void Camera::Reset()
{
	m_position = Vector2::Zero;
	m_minBoundaryX = (float)m_width;
}
