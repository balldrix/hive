#pragma once

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <directxtk/SpriteFont.h>
#include <string>

using namespace DirectX;
using namespace DirectX::Colors;
using namespace DirectX::SimpleMath;

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
	void SetOutline(bool hasOutline, Color colour = Colors::White.v);

	Vector2 GetPosition() const { return m_position; }
	Color GetColour() const { return m_colour; }
	int GetHeight() const;
	int GetWidth() const;

private:
	bool m_isActive;
	SpriteFont* m_spriteFont;
	std::string m_text;
	Vector2 m_position;
	Color m_colour;
	Color m_outlineColour;
	Vector2 m_origin;
	float m_depth;
	bool m_hasOutline;
};