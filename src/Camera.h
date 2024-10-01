#pragma once

#include "pch.h"  

class GameObject;

class Camera
{
public:
	Camera();
	~Camera();

	void			Init(float width);

	void			Update(float deltaTime);

	float			GetWidth() const { return m_width; }
	Vector2			GetPosition() const { return m_position; }

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector2& position);
	void			SetWidth(float width);
	void			SetBoundary(float x);

	void			Reset();

private:
	void			TrackTarget(float deltaTime);
	void			ClampCameraToBoundary();
	bool			TargetIsRightOfLeftThreshold(float targetX);
	bool			TargetIsLeftOfRightThreshold(float targetX);
	bool			TargetIsMovingLeft(float targetVx);
	bool			TargetIsMovingRight(float targetVx);
	void			UpdatePosition(float deltaTime);

	GameObject*		m_trackingTarget;
	Vector2			m_position;
	float			m_width;
	float			m_boundary;
	float			m_threshold;
};