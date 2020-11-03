#include "InGameHudManager.h"
#include "BarController.h"
#include "Constants.h"
#include "Graphics.h"
#include "CharacterPortrait.h"
#include "Texture.h"
#include "Sprite.h"

InGameHudManager::InGameHudManager() :
	m_playerHealthBar(nullptr),
	m_playerPortrait(nullptr),
	m_enemyPortrait(nullptr),
	m_despairFont12(nullptr),
	m_enemyId(std::string()),
	m_enemyHealthBar(nullptr),
	m_killCount(0)
{
}

InGameHudManager::~InGameHudManager()
{
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

void InGameHudManager::Init(Graphics* graphics)
{
	m_playerHealthBar = new BarController();
	m_playerHealthBar->Init(graphics);
	m_playerHealthBar->SetPosition(Vector2(InGameHudConstants::HealthBarPositionX, 
		InGameHudConstants::HealthBarPositionY));

	m_playerPortrait = new CharacterPortrait();
	m_playerPortrait->Init(graphics, "GameData//Sprites//UI//player1_hud_portrait.png");

	m_despairFont12 = new SpriteFont(graphics->GetDevice(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");
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
		Vector2(95, 2),
		Colors::YellowGreen, 0,
		Vector2::Zero
	);
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

void InGameHudManager::HideEnemyHud(std::string id)
{
	if(m_enemyId != id)
		return;

	m_enemyPortrait = nullptr;
	m_enemyHealthBar = nullptr;
	m_enemyId = std::string();
}

void InGameHudManager::SetKillCount(const int& killCount)
{
	m_killCount = killCount;
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
}
