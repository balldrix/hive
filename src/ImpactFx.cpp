#include "ImpactFx.h"

#include "Animator.h"
#include "AssetLoader.h"
#include "GameDataManager.h"
#include "Graphics.h"
#include "Spritesheet.h"
#include "Texture.h"
#include "SpriteFrameData.h"
#include "AnimatedSpriteData.h"

ImpactFx::ImpactFx() : 
	m_spritesheet(nullptr),
	m_animator(nullptr),
	m_position(0.0f, 0.0f),
	m_isActive(false)
{
}

ImpactFx::~ImpactFx()
{
}

void ImpactFx::Init()
{
	AnimatedSpriteData animatedSpriteData;
	animatedSpriteData = GameDataManager::LoadAnimatedSpriteData("assets\\data\\spritesheets\\impactfx_spritesheet.json");

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture("t_impact"), animatedSpriteData.spriteFrameData);
	m_spritesheet->SetOrigin(animatedSpriteData.origin);

	m_animator = new Animator();
	m_animator->Init(animatedSpriteData);
}

void ImpactFx::Render(Graphics* graphics)
{
	if(!m_isActive)
		return;

	auto framenum = m_animator->GetCurrentFrame();
	m_spritesheet->SetDepth(0.9f);
	m_spritesheet->Render(graphics, m_position, framenum);
}

void ImpactFx::Update(float deltaTime)
{
	if(!m_isActive)
		return;

	m_animator->Update(deltaTime);

	if(m_animator->IsDone())
		m_isActive = false;
}

void ImpactFx::DisplayFx(const Vector2& position)
{
	m_isActive = true;
	m_position = position;
	m_animator->Reset();
}
