#pragma once

#include "pch.h"

class Graphics;

class UISpriteText
{
public:
	UISpriteText();
	~UISpriteText();

	void Init(SpriteFont* spriteFont);
	void Render(Graphics* graphics);

private:
	SpriteFont* m_spriteFont;
	std::string m_text;
	Vector2 m_position;
	Color	m_colour;
	Vector2 m_origin;
};