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
	InGameUiManager();
	~InGameUiManager();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);

private:
	std::unique_ptr<SpriteFont> m_despairFont8;
	std::unique_ptr<SpriteFont> m_despairFont12;
	std::unique_ptr<SpriteFont> m_silkscreenFont8;

};

#endif _INGAME_UI_MANAGER_H_