#include "ProjectileManager.h"

#include "AABB.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "Graphics.h"
#include "Logger.h"
#include "Sprite.h"

#include <cmath>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>

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
		projectile.DeleteCollider();
	}
}

void ProjectileManager::Init(Camera* camera)
{
	Logger::LogInfo("Initialising Projectile Manager");

	m_camera = camera;

	for(auto& projectile : m_projectiles)
	{
		projectile.DeleteCollider();
	}

	m_projectiles.clear();
	m_projectiles.resize(ProjectilePoolSize);

	Sprite sprite;
	sprite.Init(AssetLoader::GetTexture("t_pixel"));

	for(auto& projectile : m_projectiles)
	{
		projectile.InitCollider(&sprite, AABB(Vector2(-2.0f, -2.0f), Vector2(2.0f, 2.0f)), Colors::OrangeRed.v);
		projectile.Init();
	}
}

void ProjectileManager::Update(float deltaTime)
{
	for(auto& projectile : m_projectiles)
	{
		if(!projectile.IsActive()) continue;
		projectile.Update(deltaTime);
	}
}

void ProjectileManager::Render(Graphics* graphics)
{
	for(auto& projectile : m_projectiles)
	{
		if(!projectile.IsActive()) continue;

		Vector2 renderPosition = projectile.GetPosition();
		if(m_camera != nullptr)
		{
			renderPosition -= m_camera->GetPosition();
		}

		projectile.Render(graphics, renderPosition);
	}
}

void ProjectileManager::SpawnProjectile(const Vector2& position, const Vector2& direction, float speed, int damage, float lifetime, GameObject* owner)
{
	for(auto& projectile : m_projectiles)
	{
		if(projectile.IsActive()) continue;

		projectile.Activate(position, direction, speed, damage, lifetime, owner);
		return;
	}
}

void ProjectileManager::DisableProjectile(Projectile& projectile)
{
	projectile.Deactivate();
}

bool ProjectileManager::IsSweptHit(const Projectile& projectile, const Collider& hurtBox) const
{
	Collider hurtBoxCopy = hurtBox;

	if(hurtBoxCopy.OnCollision(projectile.GetPosition()))
	{
		return true;
	}

	auto delta = projectile.GetPosition() - projectile.GetPreviousPosition();
	float distance = delta.Length();

	if(distance <= 0.001f)
	{
		return false;
	}

	int steps = static_cast<int>(std::ceil(distance / 2.0f));

	for(int i = 1; i <= steps; i++)
	{
		float t = static_cast<float>(i) / static_cast<float>(steps);
		Vector2 samplePoint = projectile.GetPreviousPosition() + (delta * t);
		if(hurtBoxCopy.OnCollision(samplePoint))
		{
			return true;
		}
	}

	return false;
}
