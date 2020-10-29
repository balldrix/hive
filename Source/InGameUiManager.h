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

private:
	BarController* m_playerHealthBar;
	CharacterPortrait* m_playerPortrait;
	SpriteFont* m_despairFont12;
};

#endif _INGAME_UI_MANAGER_H_