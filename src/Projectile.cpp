#include "Projectile.h"

#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "GameDataManager.h"
#include "Graphics.h"
#include "Logger.h"
#include "SpriteSheet.h"
#include "Texture.h"

#include <cmath>
#include <directxtk/SimpleMath.h>

using namespace DirectX;

Projectile::Projectile() :
	m_position(Vector2::Zero),
	m_previousPosition(Vector2::Zero),
	m_direction(Vector2::UnitX),
	m_speed(0.0f),
	m_lifetimeRemaining(0.0f),
	m_damage(0),
	m_active(false),
	m_collider(),
	m_owner(nullptr),
	m_spritesheet(nullptr),
	m_animator(nullptr)
{
}

Projectile::~Projectile()
{
	delete m_animator;
	m_animator = nullptr;

	delete m_spritesheet;
	m_spritesheet = nullptr;
}

void Projectile::Init()
{
	AnimatedSpriteData animatedSpriteData = GameDataManager::LoadAnimatedSpriteData("assets\\data\\spritesheets\\lobster-spit_spritesheet.json");
	if(animatedSpriteData.spriteFrameData.empty() || animatedSpriteData.animationStateData.empty())
	{
		Logger::LogWarning("[Projectile] Missing spritesheet frame/tag data. Projectile will render with collider debug shape.");
		return;
	}

	Texture* texture = AssetLoader::GetTexture("t_lobster-spit");
	if(texture == nullptr)
	{
		texture = AssetLoader::GetTexture("t_pixel");
	}

	if(texture == nullptr)
	{
		Logger::LogWarning("[Projectile] Missing projectile texture asset. Projectile will render with collider debug shape.");
		return;
	}

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(texture, animatedSpriteData.spriteFrameData);

	m_animator = new Animator();
	m_animator->Init("lobster-spit", animatedSpriteData, nullptr);
}

void Projectile::Update(float deltaTime)
{
	if(!m_active)
	{
		return;
	}

	m_previousPosition = m_position;
	m_position += m_direction * m_speed * deltaTime;
	m_lifetimeRemaining -= deltaTime;
	m_collider.Update(m_position);
	m_animator->Update(deltaTime);
	
	if(m_lifetimeRemaining <= 0.0f)
	{
		Deactivate();
	}
}

void Projectile::Render(Graphics* graphics, const Vector2& position)
{
	float rotation = std::atan2(m_direction.y, m_direction.x);
	rotation += 0.0f;
	m_spritesheet->SetRotation(rotation);
	m_spritesheet->SetDepth(0.85f);
	m_spritesheet->Render(graphics, position, m_animator->GetCurrentFrame());
}

void Projectile::ResetAnimation()
{
	m_animator->Reset();
}

void Projectile::InitCollider(Sprite* sprite, const AABB& bounds, const Color& colour)
{
	m_collider.Init(sprite, colour);
	m_collider.SetAABB(bounds);
	m_collider.Update(Vector2::Zero);
}

void Projectile::DeleteCollider()
{
	m_collider.Delete();
}

void Projectile::Activate(const Vector2& position, const Vector2& direction, float speed, int damage, float lifetime, GameObject* owner)
{
	Vector2 normalizedDirection = direction;
	if(normalizedDirection.LengthSquared() > 0.0001f)
	{
		normalizedDirection.Normalize();
	}
	else
	{
		normalizedDirection = Vector2::UnitX;
	}

	m_active = true;
	m_position = position;
	m_previousPosition = position;
	m_direction = normalizedDirection;
	m_speed = speed;
	m_lifetimeRemaining = lifetime;
	m_damage = damage;
	m_owner = owner;
	m_collider.Update(position);
	ResetAnimation();
}

void Projectile::Deactivate()
{
	m_active = false;
	m_position = Vector2::Zero;
	m_previousPosition = Vector2::Zero;
	m_direction = Vector2::UnitX;
	m_speed = 0.0f;
	m_lifetimeRemaining = 0.0f;
	m_damage = 0;
	m_owner = nullptr;
	m_collider.Update(Vector2::Zero);
}
