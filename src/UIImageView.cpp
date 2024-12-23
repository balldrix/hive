#include "UIImageView.h"

#include "Graphics.h"
#include "Sprite.h"

UIImageView::UIImageView() :
	m_sprite(nullptr)
{
}

UIImageView::~UIImageView()
{
	Shutdown();
}

void UIImageView::Init(std::string name)
{
	m_name = name;
	m_sprite = new Sprite();
}

void UIImageView::Render(Graphics* graphics)
{
	if(m_isActive) m_sprite->Render(graphics);
}

void UIImageView::SetPosition(Vector2 position)
{
	m_sprite->SetPosition(position);
}

void UIImageView::SetOrigin(Vector2 origin)
{
	m_sprite->SetOrigin(origin);
}

void UIImageView::SetDepth(float depth)
{
	m_sprite->SetDepth(depth);
}

void UIImageView::SetColour(Color colour)
{
	m_sprite->SetColour(colour);
}

void UIImageView::SetAlpha(float alpha)
{
	m_sprite->SetAlpha(alpha);
}

void UIImageView::Shutdown()
{
	delete m_sprite;
	m_sprite = nullptr;
}
