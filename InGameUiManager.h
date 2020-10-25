// InGameUiManager.h
// Christopher Ball 2019
// managed hud UI

#ifndef _INGAME_UI_MANAGER_H_
#define _INGAME_UI_MANAGER_H_

#include "pch.h"

class Graphics;

class InGameUiManager
{
public:
	InGameUiManager(Graphics* graphics);
	~InGameUIManager();

private:
	std::unique_ptr<SpriteFont>			m_spriteFont;

};

#endif _INGAME_UI_MANAGER_H_