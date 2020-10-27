// InGameUiManager.h
// Christopher Ball 2019
// managed hud UI

#ifndef _INGAME_UI_MANAGER_H_
#define _INGAME_UI_MANAGER_H_

#include "pch.h"

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

private:
	Texture* m_playerPortraitTexture;
	Texture* m_playerHealthBarBackgroundTexture;
	Texture* m_playerHealthBarFillTexture;
	Texture* m_playerHealthBarFrameTexture;

	Sprite* m_playerPortraitSprite;
	Sprite* m_playerHealthBarBackgroundSprite;
	Sprite* m_playerHealthBarFillSprite;
	Sprite* m_playerHealthBarFrameSprite;

	SpriteFont* m_despairFont12;
};

#endif _INGAME_UI_MANAGER_H_