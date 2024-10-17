#include "UISpriteText.h"

#include "Graphics.h"

UISpriteText::UISpriteText() :
	m_spriteFont(nullptr),
	m_text("hello, world"),
	m_position(Vector2::Zero),
	m_colour(Colors::White.v)
{
}

UISpriteText::~UISpriteText()
{
}

void UISpriteText::Init(SpriteFont* spriteFont)
{
	m_spriteFont = spriteFont;
}

void UISpriteText::Render(Graphics* graphics)
{
	m_spriteFont->DrawString(graphics->GetSpriteBatch().get(),
		m_text.c_str(),
		m_position,
		m_colour);
}
