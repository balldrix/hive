#pragma once

#include "Collider.h"

#include <directxtk/SimpleMath.h>

class Animator;
class GameObject;
class Graphics;
class Spritesheet;
class Sprite;

using namespace DirectX::SimpleMath;

class Projectile
{
public:
	Projectile();
	~Projectile();

	void Init();
	void Update(float deltaTime);
	void Render(Graphics* graphics, const Vector2& position);
	void InitCollider(Sprite* sprite, const AABB& bounds, const Color& colour);
	void DeleteCollider();
	void Activate(const Vector2& position, const Vector2& direction, float speed, int damage, float lifetime, GameObject* owner);
	void Deactivate();

	bool IsActive() const { return m_active; }
	int GetDamage() const { return m_damage; }
	GameObject* GetOwner() const { return m_owner; }
	const Vector2& GetPosition() const { return m_position; }
	const Vector2& GetPreviousPosition() const { return m_previousPosition; }
	Collider& GetCollider() { return m_collider; }
	const Collider& GetCollider() const { return m_collider; }

private:
	void ResetAnimation();

	Vector2 m_position;
	Vector2 m_previousPosition;
	Vector2 m_direction;
	float m_speed;
	float m_lifetimeRemaining;
	int m_damage;
	bool m_active;
	Collider m_collider;
	GameObject* m_owner;

	Spritesheet* m_spritesheet;
	Animator* m_animator;
};
