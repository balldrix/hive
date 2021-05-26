#include "Camera.h"

#include "GameObject.h"
#include "AudioEngine.h"

const float CameraThresholdMod = 3.0f;
const float CameraSpeedMod = 0.2f;

Camera::Camera() :
	m_trackingTarget(nullptr),
	m_position(Vector2::Zero),
	m_width(0.0f),
	m_boundary(0.0f),
	m_threshold(0.0f)
{
}

Camera::~Camera()
{
}

void Camera::Init(float width)
{
	m_width = width;
	m_threshold = m_width / CameraThresholdMod;
	m_boundary = 0.0f;
	m_position = Vector2::Zero;
}

void Camera::Update(float deltaTime)
{
	if(m_trackingTarget == nullptr)
		return;

	TrackTarget(deltaTime);
	ClampCameraToBoundary();
}

void Camera::TrackTarget(float deltaTime)
{
	float targetX = m_trackingTarget->GetPositionX();
	float targetVx = m_trackingTarget->GetTargetVelocity().x;

	if((TargetIsLeftOfRightThreshold(targetX) && TargetIsMovingRight(targetVx)) ||
	   TargetIsRightOfLeftThreshold(targetX) && TargetIsMovingLeft(targetVx))
		return;

	UpdatePosition(deltaTime);
}

void Camera::ClampCameraToBoundary()
{
	if(m_position.x < m_boundary)
		m_position.x = m_boundary;
}

bool Camera::TargetIsRightOfLeftThreshold(float targetX)
{
	return targetX > m_position.x + m_threshold;
}

bool Camera::TargetIsLeftOfRightThreshold(float targetX)
{
	return targetX < m_position.x + m_width - m_threshold;
}

bool Camera::TargetIsMovingLeft(float targetVx)
{
	return targetVx < 0.0f;
}

bool Camera::TargetIsMovingRight(float targetVx)
{
	return targetVx > 0.0f;
}

void Camera::UpdatePosition(float deltaTime)
{
	float speed = m_trackingTarget->GetMovementSpeed();
	float velocityX = m_trackingTarget->GetCurrentVelocity().x;
	
	m_position.x += velocityX * speed * deltaTime;
}

void Camera::SetTarget(GameObject* target)
{
	m_trackingTarget = target;
}

void Camera::SetPosition(const Vector2& position)
{
	m_position = position;
}

void Camera::SetWidth(float width)
{
	m_width = width;
}
	
void Camera::SetBoundary(float x)
{
	m_boundary = x;
}

void Camera::Reset()
{
	m_position = Vector2::Zero;
	m_boundary = 0.0f;
}
