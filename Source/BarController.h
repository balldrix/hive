// BarController.h
// Christopher Ball 2019-2020

#ifndef _BARCONTROLLER_H_
#define _BARCONTROLLER_H_

#include "pch.h"

class Graphics;
class Sprite;
class Texture;

class BarController
{
public:
	BarController();
	~BarController();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);
	void DeleteAll();
	void SetPosition(Vector2 position);

private:

	Texture* m_backgroundTexture;
	Texture* m_fillTexture;
	Texture* m_frameTexture;

	Sprite* m_backgroundSprite;
	Sprite* m_fillSprite;
	Sprite* m_frameSprite;
};

#endif // !_BARCONTROLLER_H_
