// GameObject.h
// Christopher Ball 2017
// A base class for objects used in game

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "pch.h"
#include "AABB.h"

// forward definitions
class Sprite;
class Graphics;

const unsigned int LERP_SPEED = 500;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	
	virtual void	Update(float deltaTime);	// update object
	virtual void 	Render(Graphics* graphics) = 0;	// render object

	float			Lerp(float target, float current, float deltaTime);

	// Setters
	virtual void	SetID(const wchar_t* string);	// set object ID
	virtual	void	SetPositionX(unsigned int x);
	virtual	void	SetPositionY(unsigned int y);
	virtual	void	SetPosition(unsigned int x, unsigned int y);
	virtual void	SetPosition(Vector2 position);	// set position

	virtual void	SetTargetMovementSpeed(float speed);
	virtual void	SetCurrentMovementSpeed(float speed);
	 
	virtual void	SetCurrentVelocity(float x, float y);
	virtual void	SetCurrentVelocity(Vector2 velocity);
	 
	virtual void	SetTargetVelocity(float x, float y);
	virtual void	SetTargetVelocity(Vector2 velocity);
	 
	virtual void	SetTargetVelocityX(float x);
	virtual void	SetTargetVelocityY(float y);
	 
	virtual void	SetActive(bool active);			// set active or not

	// getters
	virtual const wchar_t*	GetID() const		{ return m_ID; }		// return object ID
	
	virtual float			GetPositionX() const { return m_position.x; }
				
	virtual float			GetPositionY() const { return m_position.y; }

	virtual Vector2			GetPosition() const { return m_position; }

	virtual Vector2			GetCurrentVelocity() const { return m_currentVelocity; }
	virtual Vector2			GetTargetVelocity() const { return m_targetVelocity; }
	virtual float			GetTargetMovementSpeed() const { return m_targetMovementSpeed; }
	virtual float			GetCurrentMovementSpeed()	const { return m_currentMovementSpeed; }

	virtual bool			IsActive() const	{ return m_active;}		// return if active

protected:
	const wchar_t*	m_ID;					// object ID
	
	Vector2			m_position;				// object position
	Vector2			m_currentVelocity;		// current object velocity
	Vector2			m_targetVelocity;		// target velocity
	float			m_currentMovementSpeed;	// current object speed
	float			m_targetMovementSpeed;	// target movement speed

	bool			m_active;				// object active or not
};

#endif _GAMEOBJECT_H_