#pragma once

#include <string>

class Graphics;
class Sprite;
class Texture;

class CharacterPortrait
{
public:
	CharacterPortrait();
	~CharacterPortrait();

	void Init(Graphics* graphics, const std::string &texturePath);
	void Render(Graphics* graphics);
	void ReleaseAll();

private:
	void DeleteAll();

	Texture* m_playerPortraitTexture;
	Sprite* m_playerPortraitSprite;	
};