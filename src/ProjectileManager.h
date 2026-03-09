#pragma once

#include "Projectile.h"

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX::SimpleMath;

class Camera;
class Graphics;
class Collider;

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();
	void Init(Camera* camera);
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	void SpawnProjectile(const Vector2& position, const Vector2& direction, float speed, int damage, float lifetime = 2.0f, GameObject* owner = nullptr);
	std::vector<Projectile>& GetProjectiles() { return m_projectiles; }
	void DisableProjectile(Projectile& projectile);
	bool IsSweptHit(const Projectile& projectile, const Collider& hurtBox) const;

private:
	Camera* m_camera;
	std::vector<Projectile> m_projectiles;
};
