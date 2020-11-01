// CharacterPortrait.h
// Christopher Ball 2019-2020

#include <string>

class Graphics;
class Sprite;
class Texture;

class CharacterPortrait
{
public:
	CharacterPortrait();
	~CharacterPortrait();

	void Init(Graphics* graphics, std::string texturePath);
	void Render(Graphics* graphics);
	void DeleteAll();
	void ReleaseAll();

private:
	Texture* m_playerPortraitTexture;
	Sprite* m_playerPortraitSprite;
};