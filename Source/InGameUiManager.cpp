#include "InGameUiManager.h"
#include "Graphics.h"
#include "Texture.h"
#include "Sprite.h"

InGameUiManager::InGameUiManager() :
	m_playerPortraitTexture(nullptr),
	m_playerPortraitSprite(nullptr)
{
}

InGameUiManager::~InGameUiManager()
{
	if(m_playerPortraitSprite != nullptr)
	{
		delete m_playerPortraitSprite;
		m_playerPortraitSprite = nullptr;
	}

	if(m_playerPortraitTexture!= nullptr)
	{
		delete m_playerPortraitTexture;
		m_playerPortraitTexture = nullptr;
	}
}

void InGameUiManager::Init(Graphics* graphics)
{
	m_playerPortraitTexture = new Texture();
	m_playerPortraitTexture->LoadTexture(graphics, "GameData//Sprites//UI//player1_hud_portrait.png");

	m_playerPortraitSprite = new Sprite();
	m_playerPortraitSprite->Init(m_playerPortraitTexture);
	m_playerPortraitSprite->SetOrigin(Vector2::Zero);
	
	m_despairFont12 = std::make_unique<SpriteFont>(graphics->GetDevice(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");
}

void InGameUiManager::Render(Graphics* graphics)
{
	m_playerPortraitSprite->Render(graphics);

	m_despairFont12->DrawString(graphics->GetSpriteBatch(),
		L"99",
		Vector2(95, 2),
		Colors::YellowGreen, 0,
		Vector2::Zero
	);
}