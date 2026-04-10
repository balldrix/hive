#include "Camera.h"

#include "EventManager.h"
#include "GameObject.h"
#include "GlobalConstants.h"
#include "ScreenShakeEvent.h"

#include <algorithm>
#include <cmath>
#include <directxtk/SimpleMath.h>
#include <Windows.h>

using namespace GlobalConstants;

const float CameraThresholdMod = 3.0f;
const float CameraTrackingResponsiveness = 10.0f;

namespace
{
	float EaseInOut(float t)
	{
		return t * t * (3.0f - 2.0f * t);
	}

	bool UpdateBoundsTransition(float deltaTime, float duration, float& elapsed, CameraLock& lock)
	{
		elapsed += deltaTime;
		float safeDuration = (std::max)(duration, 0.001f);
		float t = (std::min)(elapsed / safeDuration, 1.0f);
		t = EaseInOut(t);

		lock.minX = std::lerp(lock.fromMinX, lock.toMinX, t);
		lock.maxX = std::lerp(lock.fromMaxX, lock.toMaxX, t);

		return t >= 1.0f;
	}

	bool UpdateFocusTransition(float deltaTime, float duration, float& elapsed, CameraCutsceneFocus& focus)
	{
		elapsed += deltaTime;
		float safeDuration = (std::max)(duration, 0.001f);
		float t = (std::min)(elapsed / safeDuration, 1.0f);
		t = EaseInOut(t);

		focus.position.x = std::lerp(focus.fromX, focus.toX, t);

		return t >= 1.0f;
	}
}

Camera::Camera() :
	m_trackingTarget(nullptr),
	m_position(Vector2::Zero),
	m_width(0.0f),
	m_boundary(0.0f),
	m_threshold(0.0f),
	m_eventManager(nullptr),
	m_skipTracking(false)
{
}

Camera::~Camera()
{
	m_eventManager->UnRegisterAllForTarget("Camera");
}

void Camera::Init(EventManager* eventManager, float width)
{
	m_width = width;
	m_threshold = m_width / CameraThresholdMod;
	m_boundary = 0.0f;
	m_position = Vector2::Zero;

	m_screenShake.Init(this);
	m_eventManager = eventManager;
	m_eventManager->RegisterEvent("ScreenShake", "Camera", new ScreenShakeEvent(&m_screenShake));
}

void Camera::Update(float deltaTime)
{
	m_screenShake.Update(deltaTime);
	
	if(m_trackingTarget == nullptr)
		return;

	if(m_cutsceneFocus.active)
	{
		if(m_cutsceneFocus.releasing)
		{
			if(UpdateFocusTransition(deltaTime, m_cutsceneFocus.releaseDuration, m_cutsceneFocus.releaseT, m_cutsceneFocus))
			{
				m_position.x = m_cutsceneFocus.toX;
				m_cutsceneFocus.releasing = false;
				m_cutsceneFocus.active = false;
				return;
			}
		}
		else if(m_cutsceneFocus.locking)
		{
			if(UpdateFocusTransition(deltaTime, m_cutsceneFocus.lockDuration, m_cutsceneFocus.lockT, m_cutsceneFocus))
			{
				m_cutsceneFocus.locking = false;
			}
		}

		UpdatePosition(deltaTime, m_cutsceneFocus.position.x);
		return;
	}

	if(m_lock.releasing)
	{
		if(UpdateBoundsTransition(deltaTime, m_lock.releaseDuration, m_lock.releaseT, m_lock))
		{
			m_lock.releasing = false;
			m_lock.active = false;
			m_skipTracking = false;
		}
	}
	else if(m_lock.locking)
	{
		if(UpdateBoundsTransition(deltaTime, m_lock.lockDuration, m_lock.lockT, m_lock))
		{
			m_lock.locking = false;
			m_lock.minX = m_lock.toMinX;
			m_lock.maxX = m_lock.toMaxX;
		}
	}

	if (!m_skipTracking) TrackTarget(deltaTime);
	ClampCameraToBoundary();
}

void Camera::BeginCutsceneFocus(float focusX, float initialX)
{
	m_cutsceneFocus.active = true;
	m_cutsceneFocus.releasing = false;
	m_cutsceneFocus.locking = true;
	m_cutsceneFocus.lockT = 0.0f;
	m_cutsceneFocus.fromX = m_position.x;
	m_cutsceneFocus.toX = focusX;
	m_cutsceneFocus.initialX = initialX;
}

void Camera::ReleaseCutsceneFocus(bool resumeTracking)
{
	m_cutsceneFocus.active = true;
	m_cutsceneFocus.releasing = true;
	m_cutsceneFocus.locking = false;
	m_cutsceneFocus.releaseT = 0.0f;
	m_cutsceneFocus.fromX = m_position.x;
	m_cutsceneFocus.toX = m_cutsceneFocus.initialX;
	m_skipTracking = !resumeTracking;
}

void Camera::TrackTarget(float deltaTime)
{
	float targetX = m_trackingTarget->GetPositionX();
	float desiredX = m_position.x;

	// Keep camera still while target is inside the dead-zone between thresholds.
	if(!TargetIsLeftOfRightThreshold(targetX))
	{
		desiredX = targetX - (m_width - m_threshold);
	}
	else if(!TargetIsRightOfLeftThreshold(targetX))
	{
		desiredX = targetX - m_threshold;
	}
	else
	{
		return;
	}

	UpdatePosition(deltaTime, desiredX);
}

void Camera::ClampCameraToBoundary()
{
	if(m_lock.active)
	{
		float left = m_lock.minX;
		float right = (std::max)(left, m_lock.maxX - m_width);
		m_position.x = std::clamp(m_position.x, left, right);
		return;
	}

	if(m_position.x < m_boundary)
		m_position.x = m_boundary;
}

bool Camera::TargetIsRightOfLeftThreshold(float targetX) const
{
	return targetX > m_position.x + m_threshold;
}

bool Camera::TargetIsLeftOfRightThreshold(float targetX) const
{
	return targetX < m_position.x + m_width - m_threshold;
}

void Camera::UpdatePosition(float deltaTime, float desiredX)
{
	float t = 1.0f - std::exp(-CameraTrackingResponsiveness * deltaTime);
	m_position.x = std::lerp(m_position.x, desiredX, t);
}

RECT Camera::GetWorldRect() const
{
	RECT rect = {};
	rect.left = m_position.x;
	rect.right = m_position.x + GameWidth;
	return rect;
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

void Camera::StartShake(float intensity, float duration)
{
	m_screenShake.Start(intensity, duration);
}

void Camera::LockBounds(float min, float max)
{
	float zoneMin = min;
	float zoneMax = (std::max)(max, zoneMin + m_width);

	m_lock.active = true;
	m_lock.releasing = false;
	m_lock.locking = true;
	m_lock.lockT = 0.0f;
	m_lock.fromMinX = m_position.x;
	m_lock.fromMaxX = m_position.x + m_width;
	m_lock.toMinX = zoneMin;
	m_lock.toMaxX = zoneMax;
	m_lock.minX = m_lock.fromMinX;
	m_lock.maxX = m_lock.fromMaxX;
}

void Camera::ReleaseBoundsSmooth(float duration, float min, float max)
{
	m_lock.active = true;
	m_lock.releasing = true;
	m_lock.locking = false;
	m_lock.releaseT = 0.0f;
	m_lock.releaseDuration = (std::max)(duration, 0.001f);
	m_lock.fromMinX = m_lock.minX;
	m_lock.fromMaxX = m_lock.maxX;
	m_lock.toMinX = min;
	m_lock.toMaxX = max;
}

void Camera::Reset()
{
	m_position = Vector2::Zero;
	m_boundary = 0.0f;
}
