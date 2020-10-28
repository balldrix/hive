#include "CharacterPortrait.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Texture.h"

CharacterPortrait::CharacterPortrait():
	m_playerPortraitTexture(nullptr),
	m_playerPortraitSprite(nullptr)
{

}

CharacterPortrait::~CharacterPortrait()
{
	DeleteAll();
}

void CharacterPortrait::Init(Graphics* graphics, std::string texturePath)
{
	m_playerPortraitTexture = new Texture();
	m_playerPortraitTexture->LoadTexture(graphics, texturePath);

	m_playerPortraitSprite = new Sprite();
	m_playerPortraitSprite->Init(m_playerPortraitTexture);
	m_playerPortraitSprite->SetOrigin(Vector2::Zero);
}

void CharacterPortrait::Render(Graphics* graphics)
{
	m_playerPortraitSprite->Render(graphics);
}

void CharacterPortrait::DeleteAll()
{
	if(m_playerPortraitSprite != nullptr)
	{
		delete m_playerPortraitSprite;
		m_playerPortraitSprite = nullptr;
	}

	if(m_playerPortraitTexture != nullptr)
	{
		delete m_playerPortraitTexture;
		m_playerPortraitTexture = nullptr;
	}
}