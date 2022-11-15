#include "InGameHudManager.h"
#include "BarController.h"
#include "InGameHudConstants.h"
#include "Graphics.h"
#include "CharacterPortrait.h"
#include "Texture.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "TravelPrompt.h"

using namespace InGameHudConstants;

const int MaxLives = 5;

InGameHudManager::InGameHudManager() :
	m_livesLeftTextures(),
	m_livesLeftSprites(),
	m_playerHealthBar(nullptr),
	m_playerPortrait(nullptr),
	m_enemyPortrait(nullptr),
	m_travelPrompt(nullptr),
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

	m_despairFont12 = new SpriteFont(graphics->GetDevice().Get(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");

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

	m_travelPrompt = new TravelPrompt();
	m_travelPrompt->Init(graphics);
}

void InGameHudManager::Render(Graphics* graphics)
{
	m_playerPortrait->Render(graphics);
	m_playerHealthBar->Render(graphics);

	if(m_enemyPortrait != nullptr)
		m_enemyPortrait->Render(graphics);

	if(m_enemyHealthBar != nullptr)
		m_enemyHealthBar->Render(graphics);

	std::string s = std::to_string(m_killCount);

	Vector2 origin = GetKillCountStringOrigin(s);

	m_despairFont12->DrawString(graphics->GetSpriteBatch().get(),
		s.c_str(),
		Vector2(KillCountPositionX, KillCountPositionY),
		Colors::YellowGreen, 0,
		origin);

	m_livesLeftSprites[m_playerLivesLeft]->Render(graphics);
	//m_travelPrompt->Render(graphics);
}

Vector2 InGameHudManager::GetKillCountStringOrigin(const std::string &s)
{
	XMVECTOR size = m_despairFont12->MeasureString(s.c_str());
	float stringSizeX = XMVectorGetX(size);
	float stringSizeY = XMVectorGetY(size);

	RECT bounds = m_despairFont12->MeasureDrawBounds(s.c_str(), Vector2::Zero);
	return Vector2(stringSizeX, stringSizeY / 2);
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
	m_travelPrompt->SetActive(true);
}

void InGameHudManager::DisableTravelPrompt()
{
	m_travelPrompt->SetActive(false);
}

void InGameHudManager::UpdatePlayerLives(const int& lives)
{
	m_playerLivesLeft = lives;
}

void InGameHudManager::HideEnemyHud(const std::string &id)
{
	if(m_enemyId != id)
		return;

	m_enemyPortrait = nullptr;
	m_enemyHealthBar = nullptr;
	m_enemyId = std::string();
}

void InGameHudManager::ShowEnemyHud(const std::string &id, Sprite* portrait, BarController* healthBar)
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

	m_travelPrompt->Release();
}

void InGameHudManager::Reset()
{
	HideEnemyHud(m_enemyId);
	m_killCount = 0;
	m_playerLivesLeft = MaxLives;
}

void InGameHudManager::DeleteAll()
{
	if(m_travelPrompt != nullptr)
	{
		delete m_travelPrompt;
		m_travelPrompt = nullptr;
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
