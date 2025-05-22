#pragma once

#include "Animator.h"
#include "DamageData.h"
#include "EventManager.h"
#include "HitBoxManager.h"
#include "SpriteSheet.h"

#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX::SimpleMath;

class Graphics;
class Sprite;
class SpriteFx;
class ControlSystem;
class Camera;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void		Init() {};

	virtual void		Update(float deltaTime);
	virtual void 		Render(Graphics* graphics) = 0;

	virtual void		Move(const Vector2& direction);
	virtual void		Stop();

	float				GetLerpAmount(const float& num) const;
	float				Lerp(float target, float current, float amount);

	// flip sprite and hitboxes
	void				FlipHorizontally(bool flip);

	// Setters
	void				SetCamera(Camera* cam);
	void				SetID(const std::string& id);
	void				SetPositionX(float x);
	void				SetPositionY(float y);
	void				SetPosition(float x, float y);
	void				SetPosition(const Vector2& position);
	void				SetMovementSpeed(float speed);
	void				SetAcceleration(float accel);
	void				SetDeceleration(float decel);
	void				SetVelocity(float x, float y);
	void				SetVelocity(const Vector2& velocity);
	void				SetCurrentVelocity(float x, float y);
	void				SetCurrentVelocity(const Vector2& velocity);
	void				SetTargetVelocity(float x, float y);
	void				SetTargetVelocity(const Vector2& velocity);
	void				SetTargetVelocityX(float x);
	void				SetTargetVelocityY(float y);
	void				SetHealth(int health);
	void				SetKnockbackCount(int count);
	void				SetGrounded(bool grounded);
	void				SetActive(bool active);

	// getters
	std::string			GetID() const { return m_id; }
	float				GetPositionX() const { return m_position.x; }
	float				GetPositionY() const { return m_position.y; }
	Vector2				GetPosition() const { return m_position; }
	Vector2				GetGroundPosition() const { return m_groundPosition; }
	Vector2				GetCurrentVelocity() const { return m_currentVelocity; }
	Vector2				GetTargetVelocity() const { return m_targetVelocity; }
	float				GetMovementSpeed()	const { return m_movementSpeed; }
	virtual DamageData 	GetDamageData() const;
	Vector3				GetFacingDirection() const { return m_facingDirection; };

	// pointers for important objects
	ControlSystem*		GetControlSystem() const { return m_controlSystem; }
	Spritesheet*		GetSprite() const { return m_spritesheet; }
	Animator*			GetAnimator() const { return m_animator; }
	HitBoxManager*		GetHitBoxManager() const { return m_hitBoxManager; }

	int					GetHealth() const { return m_health; }
	virtual int			GetMaxHealth() const;
	int					GetKnockbackCount() const { return m_knockbackCount; }
	float				GetDeathTimer() const { return m_deathTimer; }

	virtual void		ApplyDamage(GameObject* source, const int& amount);
	virtual void		Knockback(const Vector2& direction, const float& force);

	bool				IsGrounded() const { return m_grounded; }
	bool				IsDead() const { return m_dead; }
	bool				IsActive() const { return m_active; }

	void				DisplayDust(const Vector2& position);
	virtual void		PlayImpactSound() {};

	virtual void		Reset() = 0;

protected:
	std::string				m_id;
	Camera* m_camera;
	Vector2					m_position;
	Vector2					m_groundPosition;
	Vector2					m_currentVelocity;
	Vector2					m_targetVelocity;
	float					m_movementSpeed;
	float					m_acceleration;
	float					m_deceleration;
	Vector3					m_facingDirection;

	Spritesheet*			m_spritesheet;
	Animator*				m_animator;

	Sprite*					m_shadow;
	SpriteFx*				m_dustFx;

	EventManager			m_eventManager;
	HitBoxManager*			m_hitBoxManager;
	ControlSystem*			m_controlSystem;

	int						m_health;
	int						m_knockbackCount;

	float					m_deathTimer;

	bool					m_grounded;
	bool					m_dead;
	bool					m_active;
};