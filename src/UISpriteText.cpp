#include "UISpriteText.h"

#include "Graphics.h"

#include <DirectXColors.h>
#include <directxtk/SpriteFont.h>

UISpriteText::UISpriteText() :
	m_isActive(false),
	m_spriteFont(nullptr),
	m_text(""),
	m_position(Vector2::Zero),
	m_colour(Colors::White.v),
	m_depth(0.0f),
	m_origin(Vector2::Zero)
{
}

UISpriteText::~UISpriteText()
{
}

void UISpriteText::Init(SpriteFont* spriteFont)
{
	m_spriteFont = spriteFont;
	SetAlignment(Left);
}

void UISpriteText::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_spriteFont->DrawString(graphics->GetSpriteBatch().get(),
		m_text.c_str(),
		m_position,
		m_colour, 0,
		m_origin,
		Vector2::One,
		DX11::SpriteEffects_None,
		m_depth);
}

void UISpriteText::SetActive(bool isActive)
{
	m_isActive = isActive;
}

void UISpriteText::SetDepth(float depth)
{
	m_depth = depth;
}

void UISpriteText::SetText(std::string text)
{
	m_text = text;
}

void UISpriteText::SetPosition(const Vector2& position)
{
	m_position = position;
}

void UISpriteText::SetColour(const Color& colour)
{
	m_colour = colour;
}

void UISpriteText::SetAlignment(Alignments alignment)
{
	XMVECTOR measure = m_spriteFont->MeasureString(m_text.c_str());

	switch (alignment)
	{
	case UISpriteText::Left:
		m_origin = Vector2(0.0f, XMVectorGetY(measure) / 2.0f);
		break;
	case UISpriteText::Right:
		m_origin = Vector2(XMVectorGetX(measure), XMVectorGetY(measure) / 2.0f);
		break;
	case UISpriteText::Centre:
		m_origin = Vector2(XMVectorGetX(measure) / 2.0f, XMVectorGetY(measure) / 2.0f);
		break;
	default:
		break;
	}
}

int UISpriteText::GetHeight() const
{
	XMVECTOR measure = m_spriteFont->MeasureString(m_text.c_str());
	return (int)XMVectorGetY(measure);
}

int UISpriteText::GetWidth() const
{
	XMVECTOR measure = m_spriteFont->MeasureString(m_text.c_str());
	return (int)XMVectorGetX(measure);
}
