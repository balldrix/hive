#pragma once

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

class Graphics;
class Sprite;
class Texture;

class CharacterPortrait
{
public:
	CharacterPortrait();
	~CharacterPortrait();

	void Init(Graphics* graphics, Texture* texture);
	void Render(Graphics* graphics);

private:
	void DeleteAll();

	Sprite* m_playerPortraitSprite;	
};