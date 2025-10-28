#pragma once

#include "ScreenShake.h"
#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

class EventManager;
class GameObject;

class Camera
{
public:
	Camera();
	~Camera();

	void			Init(EventManager* eventManager, float width);

	void			Update(float deltaTime);

	float			GetWidth() const { return m_width; }
	Vector2			GetPosition() const { return m_position + m_screenShake.GetPositionOffset(); }

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector2& position);
	void			SetWidth(float width);
	void			SetBoundary(float x);

	void			StartShake(float intensity, float duration);

	void			Reset();

private:
	void			TrackTarget(float deltaTime);
	void			ClampCameraToBoundary();
	bool			TargetIsRightOfLeftThreshold(float targetX) const;
	bool			TargetIsLeftOfRightThreshold(float targetX) const;
	bool			TargetIsMovingLeft(float targetVx);
	bool			TargetIsMovingRight(float targetVx);
	void			UpdatePosition(float deltaTime);

	GameObject*		m_trackingTarget;
	Vector2			m_position;
	float			m_width;
	float			m_boundary;
	float			m_threshold;
	ScreenShake		m_screenShake;
	EventManager*	m_eventManager;
};