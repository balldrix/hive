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

void UIImageView::Shutdown()
{
	delete m_sprite;
	m_sprite = nullptr;
}
