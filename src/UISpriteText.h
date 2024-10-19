#pragma once

#include "pch.h"

class Graphics;

class UISpriteText
{
public:

	enum Alignments
	{
		Left,
		Right,
		Centre
	};

	UISpriteText();
	~UISpriteText();

	void Init(SpriteFont* spriteFont);
	void Render(Graphics* graphics);

	void SetActive(bool isActive);
	void SetDepth(float depth);
	void SetText(std::string text);
	void SetPosition(const Vector2& position);
	void SetColour(const Color& colour);
	void SetAlignment(Alignments alignment);

private:
	bool m_isActive;
	SpriteFont* m_spriteFont;
	std::string m_text;
	Vector2 m_position;
	Color	m_colour;
	Vector2 m_origin;
	float m_depth;
};