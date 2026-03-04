#pragma once

#include "ScreenShake.h"
#include <directxtk/SimpleMath.h>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

using namespace DirectX::SimpleMath;

class EventManager;
class GameObject;

struct CameraLock {
	bool active = false;
	float minX = 0;
	float maxX = 0;

	// for smooth release
	bool releasing = false;
	float releaseT = 0;
	float releaseDuration = 0.35f;

	float fromMinX = 0, fromMaxX = 0;
	float toMinX = 0, toMaxX = 0;
};

class Camera
{
public:
	Camera();
	~Camera();

	void			Init(EventManager* eventManager, float width);

	void			Update(float deltaTime);

	float			GetWidth() const { return m_width; }
	Vector2			GetPosition() const { return m_position + m_screenShake.GetPositionOffset(); }
	RECT			GetWorldRect() const;

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector2& position);
	void			SetWidth(float width);
	void			SetBoundary(float x);

	void			StartShake(float intensity, float duration);
	void			LockBounds(float min, float max);
	void			ReleaseBoundsSmooth(float duration, float min, float max);
	void			Reset();

private:
	void			TrackTarget(float deltaTime);
	void			ClampCameraToBoundary();
	bool			TargetIsRightOfLeftThreshold(float targetX) const;
	bool			TargetIsLeftOfRightThreshold(float targetX) const;
	void			UpdatePosition(float deltaTime, float desiredX);

	GameObject*		m_trackingTarget;
	Vector2			m_position;
	float			m_width;
	float			m_boundary;
	float			m_threshold;
	ScreenShake		m_screenShake;
	EventManager*	m_eventManager;
	CameraLock		m_lock;
};
