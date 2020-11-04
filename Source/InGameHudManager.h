// InGameHudManager.h
// Christopher Ball 2019-2020

#ifndef _INGAME_HUD_MANAGER_H_
#define _INGAME_HUD_MANAGER_H_

#include "pch.h"

class BarController;
class CharacterPortrait;
class Graphics;
class Texture;
class Sprite;

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

	void AddEnemyKill();
	void UpdatePlayerLives(const int& lives);
	void HideEnemyHud(std::string id);
	void ShowEnemyHud(std::string id, Sprite* sprite, BarController* healthBar);
	void ReleaseAll();
	void Reset();
	void DeleteAll();

private:
	std::vector<Texture*> m_livesLeftTextures;
	std::vector<Sprite*> m_livesLeftSprites;
	BarController* m_playerHealthBar;
	BarController* m_enemyHealthBar;
	CharacterPortrait* m_playerPortrait;
	Sprite* m_enemyPortrait;
	std::string m_enemyId;
	SpriteFont* m_despairFont12;
	int m_killCount;
	int m_playerLivesLeft;
};

#endif _INGAME_HUD_MANAGER_H_