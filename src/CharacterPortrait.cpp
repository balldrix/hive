#include "CharacterPortrait.h"

#include "Graphics.h"
#include "Sprite.h"

CharacterPortrait::CharacterPortrait():
	m_playerPortraitSprite(nullptr)
{
}

CharacterPortrait::~CharacterPortrait()
{
	DeleteAll();
}

void CharacterPortrait::Init(Graphics* graphics, Texture* texture)
{
	m_playerPortraitSprite = new Sprite();
	m_playerPortraitSprite->Init(texture);
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
}