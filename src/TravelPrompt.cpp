#include "TravelPrompt.h"

#include "Animator.h"
#include "InGameHudConstants.h"
#include "Spritesheet.h"
#include "Texture.h"
#include "GameObject.h"

using namespace InGameHudConstants;

TravelPrompt::TravelPrompt() 
	: m_animator(nullptr), m_texture(nullptr), m_spritesheet(nullptr) {}

TravelPrompt::~TravelPrompt() {}

void TravelPrompt::Init(Graphics* graphics)
{
	m_texture = new Texture();
	m_texture->LoadTexture(graphics, "data//Sprites//UI//go_sign.png");

	m_spritesheet = new Spritesheet();
//	m_spritesheet->Init(m_texture, "data//SpriteSheetData//travellingPromptSpritesheetData.json");
	m_spritesheet->SetPosition(Vector2(TravelPromptPositionX, TravelPromptPositionY));

	m_animator = new Animator();
	//m_animator->Init("data//AnimationData//travelPromptAnimationData.json");
	m_animator->SetAnimation("Active");

	GameObject::m_animator = m_animator;
	m_active = false;
}

void TravelPrompt::Render(Graphics* graphics)
{
	if(m_active == false)
		return;

	m_spritesheet->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->from);
}

void TravelPrompt::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
}

void TravelPrompt::Reset()
{
}

void TravelPrompt::Release()
{
	m_texture->Release();
}

void TravelPrompt::DeleteAll()
{
	if(m_animator != nullptr)
	{
		delete m_animator;
		m_animator = nullptr;
	}

	if(m_spritesheet != nullptr)
	{
		delete m_spritesheet;
		m_spritesheet = nullptr;
	}

	if(m_texture != nullptr)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}
