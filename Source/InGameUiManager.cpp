#include "InGameUiManager.h"
#include "Graphics.h"
#include "Texture.h"
#include "Sprite.h"

InGameUiManager::InGameUiManager() :
	m_playerPortraitTexture(nullptr),
	m_playerHealthBarBackgroundTexture(nullptr),
	m_playerPortraitSprite(nullptr),
	m_playerHealthBarBackgroundSprite(nullptr)
{
}

InGameUiManager::~InGameUiManager()
{
	if(m_playerHealthBarBackgroundSprite != nullptr)
	{
		delete m_playerHealthBarBackgroundSprite;
		m_playerHealthBarBackgroundSprite = nullptr;
	}

	if(m_playerPortraitSprite != nullptr)
	{
		delete m_playerPortraitSprite;
		m_playerPortraitSprite = nullptr;
	}

	if(m_playerHealthBarBackgroundTexture != nullptr)
	{
		delete m_playerHealthBarBackgroundTexture;
		m_playerHealthBarBackgroundTexture = nullptr;
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

	m_playerHealthBarBackgroundTexture = new Texture();
	m_playerHealthBarBackgroundTexture->LoadTexture(graphics, "GameData//Sprites//UI/player1_hud_healthbar_background.png");

	m_playerPortraitSprite = new Sprite();
	m_playerPortraitSprite->Init(m_playerPortraitTexture);
	m_playerPortraitSprite->SetOrigin(Vector2::Zero);

	m_playerHealthBarBackgroundSprite = new Sprite();
	m_playerHealthBarBackgroundSprite->Init(m_playerHealthBarBackgroundTexture);
	m_playerHealthBarBackgroundSprite->SetOrigin(Vector2::Zero);
	m_playerHealthBarBackgroundSprite->SetPosition(Vector2(11, 8));
	
	m_despairFont12 = std::make_unique<SpriteFont>(graphics->GetDevice(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");
}

void InGameUiManager::Render(Graphics* graphics)
{
	m_playerHealthBarBackgroundSprite->Render(graphics);
	m_playerPortraitSprite->Render(graphics);

	m_despairFont12->DrawString(graphics->GetSpriteBatch(),
		L"99",
		Vector2(95, 2),
		Colors::YellowGreen, 0,
		Vector2::Zero
	);
}