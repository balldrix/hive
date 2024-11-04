#pragma once

#include <DirectXtk/SimpleMath.h>
#include <directxtk/SpriteFont.h>
#include <string>
#include <vector>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class BarController;
class CharacterPortrait;
class Graphics;
class Sprite;
class Spritesheet;
class TravelPrompt;

class InGameHudManager
{
public:
	InGameHudManager();
	~InGameHudManager();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);
	
	void SetCurrentPlayerHealth(const int& health);
	void SetMaxPlayerHealth(const int& health);

	BarController* GetPlayerHealthBar() const { return m_playerHealthBar; }
	TravelPrompt* GetTravelPrompt() const { return m_travelPrompt; }

	void AddEnemyKill();
	void EnableTravelPrompt();
	void DisableTravelPrompt();
	void UpdatePlayerLives(const int& lives);
	void HideEnemyHud(const std::string &id);
	void ShowEnemyHud(const std::string &id, Sprite* sprite, BarController* healthBar);
	void Reset();
	void DeleteAll();

private:
	std::vector<Sprite*> m_livesLeftSprites;
	BarController* m_playerHealthBar;
	BarController* m_enemyHealthBar;
	CharacterPortrait* m_playerPortrait;
	Sprite* m_enemyPortrait;
	TravelPrompt* m_travelPrompt;
	std::string m_enemyId;
	SpriteFont* m_despairFont12;
	int m_killCount;
	int m_playerLivesLeft;

	Vector2 GetKillCountStringOrigin(const std::string &s);
};