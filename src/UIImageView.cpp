#include "UIImageView.h"

#include "Graphics.h"
#include "Texture.h"
#include "UISprite.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

UIImageView::UIImageView() :
	m_uiSprite(nullptr)
{
}

UIImageView::~UIImageView()
{
	Shutdown();
}

void UIImageView::Init(std::string name)
{
	UIView::Init(name);
	m_uiSprite = new UISprite();
}

void UIImageView::Init(std::string name, Texture* texture)
{
	UIView::Init(name);
	m_uiSprite = new UISprite();
	m_uiSprite->Init(texture);
}

void UIImageView::Render(Graphics* graphics)
{
	if(m_isActive) m_uiSprite->Render(graphics);
}

void UIImageView::SetPosition(Vector2 position)
{
	m_uiSprite->SetPosition(position);
}

void UIImageView::SetOrigin(Vector2 origin)
{
	m_uiSprite->SetOrigin(origin);
}

void UIImageView::SetDepth(float depth)
{
	m_uiSprite->SetDepth(depth);
}

void UIImageView::SetColour(Color colour)
{
	m_uiSprite->SetColour(colour);
}

void UIImageView::SetAlpha(float alpha)
{
	m_uiSprite->SetAlpha(alpha);
}

void UIImageView::SetFlipped(float flipped)
{
	SpriteEffects effects;

	if(flipped)
	{
		effects = SpriteEffects::SpriteEffects_FlipHorizontally;
	}
	else
	{
		effects = SpriteEffects::SpriteEffects_None;
	}
	
	m_uiSprite->SetFlipEffect(effects);
}

void UIImageView::Shutdown()
{
	delete m_uiSprite;
	m_uiSprite = nullptr;
}
