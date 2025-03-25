#include "UIImageView.h"

#include "Graphics.h"
#include "UISprite.h"

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
	m_name = name;
	m_uiSprite = new UISprite();
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

void UIImageView::Shutdown()
{
	delete m_uiSprite;
	m_uiSprite = nullptr;
}
