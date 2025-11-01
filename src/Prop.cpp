#include "Prop.h"

#include "AABB.h"
#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "Collider.h"
#include "GameDataManager.h"
#include "GameObject.h"
#include "Graphics.h"
#include "PropManager.h"
#include "SpriteFrameData.h"
#include "SpriteSheet.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>
#include <vector>

Prop::Prop() :
	GameObject(),
	m_collider(),
	m_isAnimated(false),
	m_isBreakable(false),
	m_hasBroken(false)
{
}

Prop::~Prop()
{
	Shutdown();
}

void Prop::Init(const std::string& id, Camera* camera, const Vector2& position, Collider collider, bool isAnimated, bool isBreakable, PropManager* propManager)
{
	m_id = id;
	m_camera = camera;
	m_position = position;
	m_collider = collider;
	m_isAnimated = isAnimated;
	m_isBreakable = isBreakable;
	m_propManager = propManager;

	std::vector<SpriteFrameData> spriteFrameData;

	if(isAnimated || isBreakable)
	{
		AnimatedSpriteData animatedSpriteData = GameDataManager::LoadAnimatedSpriteData(fmt::format("assets\\data\\spritesheets\\{0}_spritesheet.json", id));
		spriteFrameData = animatedSpriteData.spriteFrameData;
		m_animator = new Animator();
		m_animator->Init(m_id, animatedSpriteData, nullptr);
	}

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture(fmt::format("t_{0}", id)), spriteFrameData);
	m_spritesheet->SetOrigin(Vector2::Zero);
}

void Prop::Update(float deltaTime)
{
	if(m_animator) m_animator->Update(deltaTime);

	if(m_hasBroken && m_animator && m_animator->IsDone())
	{
		m_propManager->Remove(this);
	}
}

void Prop::Render(Graphics* graphics)
{
	m_spritesheet->SetDepth(m_position.y / graphics->GetBackbufferHeight());

	if(m_isAnimated || m_isBreakable)
	{
		m_spritesheet->Render(graphics, m_position - m_camera->GetPosition(), m_animator->GetCurrentFrame());
		return;
	}

	m_spritesheet->Render(graphics, m_position - m_camera->GetPosition());
}

void Prop::Break()
{
	m_hasBroken = true;
	m_animator->SetAnimation("break");
}

void Prop::Shutdown()
{
	delete m_spritesheet;
	m_spritesheet = nullptr;

	delete m_animator;
	m_animator = nullptr;
}