#pragma once

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

	void SetCurrentValue(const int& value);
	void SetMaxValue(const int& value);
	void SetPosition(const Vector2& position);
	void SetWidth(const unsigned int& width);

	unsigned int GetWidth() const { return m_width; }

	void ReleaseAll();

private:
	int		m_currentValue;
	int		m_maxValue;

	Texture* m_backgroundTexture;
	Texture* m_fillTexture;
	Texture* m_frameTexture;

	Sprite* m_backgroundSprite;
	Sprite* m_fillSprite;
	Sprite* m_frameSprite;

	unsigned int    m_width;
};
