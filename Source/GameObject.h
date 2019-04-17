// GameObject.h
// Christopher Ball 2019
// A base class for objects used in game

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "pch.h"

// forward definitions
class Graphics;
class HitBoxManager;
class Sprite;
class SpriteSheet;
class Animator;
class ControlSystem;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	
	virtual void	Init(const Vector2& position, Sprite* sprite);
	virtual void	Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager);
	virtual void	Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);

	virtual void	Update(float deltaTime);	// update object
	virtual void 	Render(Graphics* graphics) = 0;	// render object

	virtual void	Move(const Vector2 &direction);
	virtual void	Stop();

	float			GetLerpAmount(float num);
	float			Lerp(float target, float current, float amount);

	// flip sprite and hitboxes
	void			FlipHorizontally(bool flip);

	// Setters
	void			SetID(const wchar_t* string);	// set object ID
	void			SetPositionX(unsigned int x);
	void			SetPositionY(unsigned int y);
	void			SetPosition(unsigned int x, unsigned int y);
	void			SetPosition(Vector2 position);	// set position
	void			SetMovementSpeed(float speed);
	void			SetCurrentVelocity(float x, float y);
	void			SetCurrentVelocity(Vector2 velocity);
	void			SetTargetVelocity(float x, float y);
	void			SetTargetVelocity(Vector2 velocity);
	void			SetTargetVelocityX(float x);
	void			SetTargetVelocityY(float y);
	void			SetAcceleration(float accel);
	void			SetActive(bool active);			// set active or not

	// getters
	const wchar_t*	GetID() const		{ return m_ID; }					// return object ID
	float			GetPositionX() const { return m_position.x; }
	float			GetPositionY() const { return m_position.y; }
	Vector2			GetPosition() const { return m_position; }
	Vector2			GetCurrentVelocity() const { return m_currentVelocity; }
	Vector2			GetTargetVelocity() const { return m_targetVelocity; }
	float			GetMovementSpeed()	const { return m_movementSpeed; }

	// pointers for important objects
	ControlSystem*	GetControlSystem() const { return m_controlSystem; }
	SpriteSheet*	GetSprite() const { return m_sprite; }
	Animator*		GetAnimator() const { return m_animator; }
	HitBoxManager*	GetHitBoxManager() const { return m_hitBoxManager; }

	// apply damage
	virtual void	ApplyDamage(int amount);

	bool			IsActive() const	{ return m_active;}		// return if active

protected:
	const wchar_t*	m_ID;					// object ID

	Vector2			m_position;				// object position
	Vector2			m_currentVelocity;		// current object velocity
	Vector2			m_targetVelocity;		// target velocity
	float			m_movementSpeed;		// current object speed
	float			m_acceleration;			// acceleration speed
	float			m_deceleration;			// decceleration speed

	SpriteSheet*	m_sprite;				// object sprite sheet
	Animator*		m_animator;				// animation controller

	HitBoxManager*	m_hitBoxManager;		// hit box manager
	ControlSystem*	m_controlSystem;		// pointer to control system	

	bool			m_active;				// object active or not
};

#endif _GAMEOBJECT_H_