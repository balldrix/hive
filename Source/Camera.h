#pragma once

#include "pch.h"  

class GameObject;

class Camera
{
public:
	Camera();
	~Camera();

	void			Init(float width, float height);

	void			Update(float deltaTime);

	float			GetWidth() const { return m_width; }
	Vector3			GetPosition() const { return m_position; }

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector3& position);
	void			SetWidth(float width);
	void			SetBoundary(float x);

	Matrix			GetViewMatrix() const { return m_viewMatrix; }
	Matrix			GetProjectionMatrix() const { return m_projectionMatrix; }

	void			Reset();

private:
	void			SetProjectionMatrix();
	void			SetViewMatrix();
	void			TrackTarget(float deltaTime);
	void			ClampCameraToBoundary();
	bool			TargetIsRightOfLeftThreshold(float targetX);
	bool			TargetIsLeftOfRightThreshold(float targetX);
	bool			TargetIsMovingLeft(float targetVx);
	bool			TargetIsMovingRight(float targetVx);
	void			UpdatePosition(float deltaTime);

	GameObject*		m_trackingTarget;
	Vector3			m_position;

	Matrix			m_viewMatrix;
	Matrix			m_projectionMatrix;

	float			m_width;
	float			m_height;
	float			m_boundary;
	float			m_threshold;
};