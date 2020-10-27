#include "InGameUiManager.h"
#include "Graphics.h"
#include "Texture.h"
#include "Sprite.h"

InGameUiManager::InGameUiManager() :
	m_playerPortraitTexture(nullptr),
	m_playerHealthBarBackgroundTexture(nullptr),
	m_playerHealthBarFillTexture(nullptr),
	m_playerPortraitSprite(nullptr),
	m_playerHealthBarBackgroundSprite(nullptr),
	m_playerHealthBarFillSprite(nullptr),
	m_despairFont12(nullptr)
{
}

InGameUiManager::~InGameUiManager()
{
	if(m_despairFont12 != nullptr)
	{
		delete m_despairFont12;
		m_despairFont12 = nullptr;
	}

	if(m_playerHealthBarFillSprite != nullptr)
	{
		delete m_playerHealthBarFillSprite;
		m_playerHealthBarFillSprite = nullptr;
	}

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

	if(m_playerHealthBarFillTexture != nullptr)
	{
		delete m_playerHealthBarFillTexture;
		m_playerHealthBarFillTexture = nullptr;
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

	m_playerHealthBarFillTexture = new Texture();
	m_playerHealthBarFillTexture->LoadTexture(graphics, "GameData//Sprites//UI/player1_hud_healthbar_fill.png");

	m_playerPortraitSprite = new Sprite();
	m_playerPortraitSprite->Init(m_playerPortraitTexture);
	m_playerPortraitSprite->SetOrigin(Vector2::Zero);

	m_playerHealthBarBackgroundSprite = new Sprite();
	m_playerHealthBarBackgroundSprite->Init(m_playerHealthBarBackgroundTexture);
	m_playerHealthBarBackgroundSprite->SetOrigin(Vector2::Zero);
	m_playerHealthBarBackgroundSprite->SetPosition(Vector2(11, 8));
	
	m_playerHealthBarFillSprite = new Sprite();
	m_playerHealthBarFillSprite->Init(m_playerHealthBarFillTexture);
	m_playerHealthBarFillSprite->SetOrigin(Vector2::Zero);
	m_playerHealthBarFillSprite->SetPosition(Vector2(11, 8));

	m_despairFont12 = new SpriteFont(graphics->GetDevice(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");
}

void InGameUiManager::Render(Graphics* graphics)
{
	m_playerHealthBarBackgroundSprite->Render(graphics);
	m_playerHealthBarFillSprite->Render(graphics);

	m_playerPortraitSprite->Render(graphics);

	m_despairFont12->DrawString(graphics->GetSpriteBatch(),
		L"99",
		Vector2(95, 2),
		Colors::YellowGreen, 0,
		Vector2::Zero
	);
}