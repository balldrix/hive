#include "UIStackingView.h"

UIStackingView::UIStackingView() :
	m_childViews(0),
	m_orientation(UIStackingView::Orientations::Horizontal),
	m_spacing(0),
	m_stackedViewsHeight(0),
	m_stackedViewsWidth(0)
{
}

UIStackingView::~UIStackingView()
{
	Shutdown();
}

void UIStackingView::Init(std::string name)
{
	m_name = name;
	m_spacing = 20;
}

void UIStackingView::Render(Graphics* graphics)
{
	for(UIView* i : m_childViews)
	{
		i->Render(graphics);
	}
}

void UIStackingView::SetHeight(int height)
{
	m_stackedViewsHeight = height;
}

void UIStackingView::SetWidth(int width)
{
	m_stackedViewsWidth = width;
}

void UIStackingView::Shutdown()
{
	for(UIView* i : m_childViews)
	{
		delete i;
		i = nullptr;
	}

	m_childViews.clear();
}