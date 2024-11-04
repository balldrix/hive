#pragma once

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

class Graphics;
class Texture;
class Sprite;

class BarController
{
public:
	BarController();
	~BarController();

	void Init(Graphics* graphics, Texture* backgroundTexture, Texture* fillTexture, Texture* frameTexture);
	void Render(Graphics* graphics);
	void DeleteAll();

	void SetCurrentValue(const int& value);
	void SetMaxValue(const int& value);
	void SetPosition(const Vector2& position);
	void SetWidth(const unsigned int& width);

	unsigned int GetWidth() const { return m_width; }

private:
	int		m_currentValue;
	int		m_maxValue;

	Sprite* m_backgroundSprite;
	Sprite* m_fillSprite;
	Sprite* m_frameSprite;

	unsigned int    m_width;
};
