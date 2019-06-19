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

	void			Init(unsigned int width, unsigned int height, unsigned int worldWidth);

	void			Update(float deltaTime);

	Vector2			GetPosition() const { return m_position; }
	unsigned int	GetWidth() const { return m_width; }
	unsigned int	GetHeight() const { return m_height; }

	void			SetTarget(GameObject* target);
	void			SetPosition(const Vector2& position);
	void			SetWidth(unsigned int width);
	void			SetHeight(unsigned int height);

	void			Reset();

private:
	GameObject*		m_trackingTarget;
	Vector2			m_position;
	Vector2			m_origin;
	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_maxWidth;
};

#endif // !_CAMERA_H_
