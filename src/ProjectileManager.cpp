#include "ProjectileManager.h"

#include "AABB.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "Graphics.h"
#include "Logger.h"
#include "Sprite.h"

#include <cmath>
#include <DirectXColors.h>

using namespace DirectX;

namespace
{
	constexpr size_t ProjectilePoolSize = 64;
}

ProjectileManager::ProjectileManager()
	: m_camera(nullptr),
	m_projectiles()
{
}

ProjectileManager::~ProjectileManager()
{
	for(auto& projectile : m_projectiles)
	{
		projectile.collider.Delete();
	}
}

void ProjectileManager::Init(Camera* camera)
{
	Logger::LogInfo("Initialising Projectile Manager");

	m_camera = camera;

	for(auto& projectile : m_projectiles)
	{
		projectile.collider.Delete();
	}

	m_projectiles.clear();
	m_projectiles.resize(ProjectilePoolSize);

	Sprite sprite;
	sprite.Init(AssetLoader::GetTexture("t_pixel"));

	for(auto& projectile : m_projectiles)
	{
		projectile.collider.Init(&sprite, Colors::OrangeRed.v);
		projectile.collider.SetAABB(AABB(Vector2(-2.0f, -2.0f), Vector2(2.0f, 2.0f)));
		projectile.collider.Update(Vector2::Zero);
	}
}

void ProjectileManager::Update(float deltaTime)
{
	for(auto& projectile : m_projectiles)
	{
		if(!projectile.active) continue;

		projectile.previousPosition = projectile.position;
		projectile.position += projectile.direction * projectile.speed * deltaTime;
		projectile.lifetimeRemaining -= deltaTime;
		projectile.collider.Update(projectile.position);

		if(projectile.lifetimeRemaining <= 0.0f)
		{
			DisableProjectile(projectile);
		}
	}
}

void ProjectileManager::Render(Graphics* graphics)
{
	for(auto& projectile : m_projectiles)
	{
		if(!projectile.active) continue;

		Vector2 renderPosition = projectile.position;
		if(m_camera != nullptr)
		{
			renderPosition -= m_camera->GetPosition();
		}

		projectile.collider.Render(graphics, renderPosition);
	}
}

void ProjectileManager::SpawnProjectile(const Vector2& position, const Vector2& direction, float speed, int damage, float lifetime, GameObject* owner)
{
	for(auto& projectile : m_projectiles)
	{
		if(projectile.active) continue;

		Vector2 normalizedDirection = direction;
		if(normalizedDirection.LengthSquared() > 0.0001f)
		{
			normalizedDirection.Normalize();
		}
		else
		{
			normalizedDirection = Vector2::UnitX;
		}

		projectile.active = true;
		projectile.position = position;
		projectile.previousPosition = position;
		projectile.direction = normalizedDirection;
		projectile.speed = speed;
		projectile.lifetimeRemaining = lifetime;
		projectile.damage = damage;
		projectile.owner = owner;
		projectile.collider.Update(position);
		return;
	}
}

void ProjectileManager::DisableProjectile(Projectile& projectile)
{
	projectile.active = false;
	projectile.position = Vector2::Zero;
	projectile.previousPosition = Vector2::Zero;
	projectile.direction = Vector2::UnitX;
	projectile.speed = 0.0f;
	projectile.lifetimeRemaining = 0.0f;
	projectile.damage = 0;
	projectile.owner = nullptr;
	projectile.collider.Update(Vector2::Zero);
}

bool ProjectileManager::IsSweptHit(const Projectile& projectile, const Collider& hurtBox) const
{
	Collider hurtBoxCopy = hurtBox;

	if(hurtBoxCopy.OnCollision(projectile.position))
	{
		return true;
	}

	auto delta = projectile.position - projectile.previousPosition;
	float distance = delta.Length();

	if(distance <= 0.001f)
	{
		return false;
	}

	int steps = static_cast<int>(std::ceil(distance / 2.0f));

	for(int i = 1; i <= steps; i++)
	{
		float t = static_cast<float>(i) / static_cast<float>(steps);
		Vector2 samplePoint = projectile.previousPosition + (delta * t);
		if(hurtBoxCopy.OnCollision(samplePoint))
		{
			return true;
		}
	}

	return false;
}
