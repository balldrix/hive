#include "InGameHudManager.h"
#include "BarController.h"
#include "Constants.h"
#include "Graphics.h"
#include "CharacterPortrait.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteSheet.h"

using namespace InGameHudConstants;

const int MaxLives = 5;

InGameHudManager::InGameHudManager() :
	m_livesLeftTextures(),
	m_livesLeftSprites(),
	m_playerHealthBar(nullptr),
	m_playerPortrait(nullptr),
	m_enemyPortrait(nullptr),
	m_travelPromptTexture(nullptr),
	m_travelPromptSpritesheet(nullptr),
	m_despairFont12(nullptr),
	m_enemyId(std::string()),
	m_enemyHealthBar(nullptr),
	m_killCount(0),
	m_playerLivesLeft(0)
{
}

InGameHudManager::~InGameHudManager()
{
	DeleteAll();
}

void InGameHudManager::Init(Graphics* graphics)
{
	m_playerHealthBar = new BarController();
	m_playerHealthBar->Init(graphics);
	m_playerHealthBar->SetPosition(Vector2(HealthBarPositionX, HealthBarPositionY));

	m_playerPortrait = new CharacterPortrait();
	m_playerPortrait->Init(graphics, "GameData//Sprites//UI//player1_hud_portrait.png");

	m_despairFont12 = new SpriteFont(graphics->GetDevice(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");

	m_playerLivesLeft = MaxLives;

	for(size_t i = 0; i <= MaxLives; i++)
	{
		Texture* texture = new Texture();
		std::string filePath = "GameData//Sprites//UI//lives_x" + std::to_string(i) + ".png";
		texture->LoadTexture(graphics, filePath);
		m_livesLeftTextures.push_back(texture);
	}

	for(size_t i = 0; i <= MaxLives; i++)
	{
		Sprite* sprite = new Sprite();
		sprite->Init(m_livesLeftTextures[i]);
		sprite->SetOrigin(Vector2::Zero);
		sprite->SetPosition(Vector2(LifeCounterPositionX, LifeCounterPositionY));
		m_livesLeftSprites.push_back(sprite);
	}

	m_travelPromptTexture = new Texture();
	m_travelPromptTexture->LoadTexture(graphics, "GameData//Sprites//UI//go_sign.png");

	m_travelPromptSpritesheet = new SpriteSheet();
	m_travelPromptSpritesheet->Init(m_travelPromptTexture, "GameData//SpriteSheetData//travellingPromptSpritesheetData.json");
	m_travelPromptSpritesheet->SetPosition(Vector2(TravelPromptPositionX, TravelPromptPositionY));
}

void InGameHudManager::Render(Graphics* graphics)
{
	m_playerPortrait->Render(graphics);
	m_playerHealthBar->Render(graphics);

	if(m_enemyPortrait != nullptr)
		m_enemyPortrait->Render(graphics);

	if(m_enemyHealthBar != nullptr)
		m_enemyHealthBar->Render(graphics);

	m_despairFont12->DrawString(graphics->GetSpriteBatch(),
		std::to_string(m_killCount).c_str(),
		Vector2(105, 0),
		Colors::YellowGreen, 0,
		Vector2::Zero);

	m_livesLeftSprites[m_playerLivesLeft]->Render(graphics);

	m_travelPromptSpritesheet->Render(graphics, 0);
}

void InGameHudManager::SetCurrentPlayerHealth(const int& health)
{
	m_playerHealthBar->SetCurrentValue(health);
}

void InGameHudManager::SetMaxPlayerHealth(const int& health)
{
	m_playerHealthBar->SetMaxValue(health);
}

void InGameHudManager::AddEnemyKill()
{
	m_killCount++;
}

void InGameHudManager::EnableTravelPrompt()
{
	
}

void InGameHudManager::UpdatePlayerLives(const int& lives)
{
	m_playerLivesLeft = lives;
}

void InGameHudManager::HideEnemyHud(std::string id)
{
	if(m_enemyId != id)
		return;

	m_enemyPortrait = nullptr;
	m_enemyHealthBar = nullptr;
	m_enemyId = std::string();
}

void InGameHudManager::ShowEnemyHud(std::string id, Sprite* portrait, BarController* healthBar)
{
	m_enemyId = id;
	m_enemyPortrait = portrait;
	m_enemyHealthBar = healthBar;
}

void InGameHudManager::ReleaseAll()
{
	m_playerHealthBar->ReleaseAll();
	m_playerPortrait->ReleaseAll();

	for(size_t i = 0; i < m_livesLeftTextures.size(); i++)
	{
		m_livesLeftTextures[i]->Release();
	}

	m_travelPromptTexture->Release();
}

void InGameHudManager::Reset()
{
	HideEnemyHud(m_enemyId);
	m_killCount = 0;
	m_playerLivesLeft = MaxLives;
}

void InGameHudManager::DeleteAll()
{
	if(m_travelPromptSpritesheet != nullptr)
	{
		delete m_travelPromptSpritesheet;
		m_travelPromptSpritesheet = nullptr;
	}

	if(m_travelPromptTexture != nullptr)
	{
		delete m_travelPromptTexture;
		m_travelPromptTexture = nullptr;
	}

	for(size_t i = m_livesLeftSprites.size(); i--;)
	{
		if(m_livesLeftSprites[i] != nullptr)
		{
			delete m_livesLeftSprites[i];
			m_livesLeftSprites[i] = nullptr;
		}
	}

	for(size_t i = m_livesLeftTextures.size(); i--;)
	{
		if(m_livesLeftTextures[i] != nullptr)
		{
			delete m_livesLeftTextures[i];
			m_livesLeftTextures[i] = nullptr;
		}
	}

	m_livesLeftTextures.clear();

	if(m_despairFont12 != nullptr)
	{
		delete m_despairFont12;
		m_despairFont12 = nullptr;
	}

	if(m_playerPortrait != nullptr)
	{
		delete m_playerPortrait;
		m_playerPortrait = nullptr;
	}

	if(m_playerHealthBar != nullptr)
	{
		delete m_playerHealthBar;
		m_playerHealthBar = nullptr;
	}
}
