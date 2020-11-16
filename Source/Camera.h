// Camera.h
// Christopher Ball 2019
// tracks camera position

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "pch.h"  

class GameObject;

class Camera
{
public:
	Camera();
	~Camera();

	void			Init(unsigned int width, unsigned int maxBoundary);

	void			Update(float deltaTime);

	unsigned int	GetWidth() const { return m_width; }
	Vector2			GetPosition() const { return m_position; }

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector2& position);
	void			SetWidth(unsigned int width);
	void			SetBoundary(float x);

	void			Reset();

private:
	GameObject*		m_trackingTarget;
	Vector2			m_position;
	unsigned int	m_width;
	float			m_minBoundaryX;
	float			m_maxBoundaryX;
};

#endif // !_CAMERA_H_
