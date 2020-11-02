// InGameUiManager.h
// Christopher Ball 2019-2020

#ifndef _INGAME_UI_MANAGER_H_
#define _INGAME_UI_MANAGER_H_

#include "pch.h"

class BarController;
class CharacterPortrait;
class Graphics;
class Texture;
class Sprite;

class InGameUiManager
{
public:
	InGameUiManager();
	~InGameUiManager();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);
	
	void SetCurrentPlayerHealth(const int& health);
	void SetMaxPlayerHealth(const int& health);

	BarController* GetPlayerHealthBar() const { return m_playerHealthBar; }

	void AddEnemyKill();
	void DisablePortrait(std::string id, Sprite* sprite);
	void SetKillCount(const int& kills);
	void DisplayEnemyPortrait(std::string id, Sprite* sprite);
	void ReleaseAll();

private:
	BarController* m_playerHealthBar;
	CharacterPortrait* m_playerPortrait;
	Sprite* m_enemyPortrait;
	std::string m_enemyId;
	SpriteFont* m_despairFont12;
	int m_killCount;
};

#endif _INGAME_UI_MANAGER_H_