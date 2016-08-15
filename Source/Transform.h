#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "pch.h"

const unsigned int LERP_SPEED = 500;

class Transform
{
public:
	Transform();
	~Transform();

	virtual void				Update(float deltaTime);
	virtual	void				Reset();

	// create smooth movement with linear interpolation
	float						Lerp(float target, float current, float deltaTime);
		
	void						SetPositionX(unsigned int x);
	void						SetPositionY(unsigned int y);
	void						SetPosition(unsigned int x, unsigned int y);
	void						SetPosition(Vector2 position);
	void						SetTargetMovementSpeed(unsigned int speed);
	void						SetCurrentMovementSpeed(unsigned int speed);
	void						SetCurrentVelocity(float x, float y);
	void						SetCurrentVelocity(Vector2 velocity);
	void						SetTargetVelocity(float x, float y);
	void						SetTargetVelocity(Vector2 velocity);
	void						SetTargetVelocityX(float x);
	void						SetTargetVelocityY(float y);

	unsigned int				GetPositionX() const { return m_position.x;	}
	unsigned int				GetPositionY() const { return m_position.y; }
	Vector2					GetPosition() const { return m_position; }
	Vector2					GetCurrentVelocity() const { return m_currentVelocity; }
	Vector2					GetTargetVelocity() const {	return m_targetVelocity; }
	float						GetTargetMovementSpeed() const { return m_targetMovementSpeed; } 
	float						GetCurrentMovementSpeed()	const { return m_currentMovementSpeed;	}
	
protected:
	Vector2	m_position;
	Vector2	m_currentVelocity;
	Vector2	m_targetVelocity;

	float		m_currentMovementSpeed;
	float		m_targetMovementSpeed;

	// does object need interpolation for movements
	bool		m_isLerper;
};

#endif	_TRANSFORM_H_