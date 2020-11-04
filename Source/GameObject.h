// GameObject.h
// Christopher Ball 2019
// A base class for objects used in game

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "pch.h"
#include "HitBoxManager.h"

using std::string;
using std::map;

// forward definitions
class Graphics;
class Sprite;
class SpriteSheet;
class Animator;
class ControlSystem;
class Camera;

struct ObjectData
{
	std::string				id;
	unsigned int			startingHealth;
	unsigned int			startingLives;
	Vector2					startingPosition;
	float					walkSpeed;
	float					runningSpeed;
	float					acceleration;
	float					deceleration;
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void	Init(const Vector2& position, Sprite* sprite);
	virtual void	Init(const Vector2& position, Sprite* sprite, Sprite* shadow);
	virtual void	Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager);
	virtual void	Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager);
	virtual void	Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);
	virtual void	Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem);

	virtual void	Update(float deltaTime);	// update object
	virtual void 	Render(Graphics* graphics) = 0;	// render object

	virtual void	Move(const Vector2& direction);
	virtual void	Stop();

	float			GetLerpAmount(float num);
	float			Lerp(float target, float current, float amount);
	bool			LoadDamageData(std::string damageDataFile);

	// flip sprite and hitboxes
	void			FlipHorizontally(bool flip);

	// Setters
	void			SetCamera(Camera* cam);
	void			SetID(std::string id);			// set object ID
	void			SetPositionX(unsigned int x);
	void			SetPositionY(unsigned int y);
	void			SetPosition(unsigned int x, unsigned int y);
	void			SetPosition(const Vector2& position);			// set position
	void			SetMovementSpeed(float speed);
	void			SetAcceleration(float accel);
	void			SetDeceleration(float decel);
	void			SetVelocity(float x, float y);
	void			SetVelocity(const Vector2& velocity);
	void			SetCurrentVelocity(float x, float y);
	void			SetCurrentVelocity(const Vector2& velocity);
	void			SetTargetVelocity(float x, float y);
	void			SetTargetVelocity(const Vector2& velocity);
	void			SetTargetVelocityX(float x);
	void			SetTargetVelocityY(float y);
	void			SetHealth(int health);
	void			SetKnockbackCount(int count);
	void			SetGrounded(bool grounded);
	void			SetActive(bool active);					// set active or not

	// getters
	std::string		GetID() const { return m_id; }					// return object ID
	float			GetPositionX() const { return m_position.x; }
	float			GetPositionY() const { return m_position.y; }
	Vector2			GetPosition() const { return m_position; }
	Vector2			GetGroundPosition() const { return m_groundPosition; }
	Vector2			GetCurrentVelocity() const { return m_currentVelocity; }
	Vector2			GetTargetVelocity() const { return m_targetVelocity; }
	float			GetMovementSpeed()	const { return m_movementSpeed; }
	virtual int		GetDamage() const;

	// pointers for important objects
	ControlSystem*	GetControlSystem() const { return m_controlSystem; }
	SpriteSheet*	GetSprite() const { return m_sprite; }
	Animator*		GetAnimator() const { return m_animator; }
	HitBoxManager*	GetHitBoxManager() const { return m_hitBoxManager; }

	int				GetHealth() const { return m_health; }
	virtual int		GetMaxHealth() const;
	int				GetKnockbackCount() const { return m_knockbackCount; }
	float			GetDeathTimer() const { return m_deathTimer; }

	virtual void	ApplyDamage(GameObject* source, const int& amount); // apply damage
	virtual void	Knockback(const Vector2& direction, const float& force); // knock back with force

	bool			IsGrounded() const { return m_grounded; }
	bool			IsDead() const { return m_dead; }
	bool			IsActive() const { return m_active; }		// return if active
	
	virtual void	Reset() = 0;	// must override reset method

protected:
 	std::string			m_id;					// object ID
	Camera*				m_camera;				// pointer to camera
	Vector2				m_position;				// object position
	Vector2				m_groundPosition;		// y position of grounded feet
	Vector2				m_currentVelocity;		// current object velocity
	Vector2				m_targetVelocity;		// target velocity
	float				m_movementSpeed;		// current object speed
	float				m_acceleration;			// acceleration speed
	float				m_deceleration;			// decceleration speed

	SpriteSheet*		m_sprite;				// object sprite sheet
	Animator*			m_animator;				// animation controller

	Sprite*				m_shadow;				// object shadow

	HitBoxManager*		m_hitBoxManager;		// hit box manager
	ControlSystem*		m_controlSystem;		// pointer to control system	

	int					m_health;				// object health
	int					m_knockbackCount;		// number of knockbacks

	float				m_deathTimer;			// timer running while object is dead

	bool				m_grounded;				// true when object is grounded
	bool				m_dead;					// true when object is dead/destroyed
	bool				m_active;				// object active or not
	map<string, int>	m_damageData;			// damage data map
};

#endif _GAMEOBJECT_H_