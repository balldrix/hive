#include "SpriteFx.h"

#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "GameDataManager.h"
#include "Graphics.h"
#include "Spritesheet.h"

#include <directxtk/SimpleMath.h>
#include <string>

SpriteFx::SpriteFx() : 
	m_spritesheet(nullptr),
	m_animator(nullptr),
	m_position(0.0f, 0.0f),
	m_isActive(false)
{
}

SpriteFx::~SpriteFx()
{
}

void SpriteFx::Init(std::string textureId, std::string spriteId)
{
	AnimatedSpriteData animatedSpriteData;
	animatedSpriteData = GameDataManager::LoadAnimatedSpriteData(spriteId);

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture(textureId), animatedSpriteData.spriteFrameData);
	m_spritesheet->SetOrigin(animatedSpriteData.origin);

	m_animator = new Animator();
	m_animator->Init(animatedSpriteData);
}

void SpriteFx::Render(Graphics* graphics)
{
	if(!m_isActive)
		return;

	auto framenum = m_animator->GetCurrentFrame();
	m_spritesheet->SetDepth(0.9f);
	m_spritesheet->Render(graphics, m_position, framenum);
}

void SpriteFx::Update(float deltaTime)
{
	if(!m_isActive)
		return;

	m_animator->Update(deltaTime);

	if(m_animator->IsDone())
		m_isActive = false;
}

void SpriteFx::DisplayFx(const Vector2& position)
{
	m_isActive = true;
	m_position = position;
	m_animator->Reset();
}
