// GameOverScreen.h
// Christopher Ball 2019-2020

#pragma once

#include <string>

class Graphics;
class Texture;
class SpriteSheet;

class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void Init(Graphics* graphics, std::string textureFile);
	void Render(Graphics* graphics);
	void ReleaseAll();
private:
	void DeleteAll();

	Graphics* m_graphics;
	Texture* m_gameOverTexture;
	SpriteSheet* m_gameOverTexture;
	
};