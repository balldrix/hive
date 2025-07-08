#include "UIStackingView.h"

#include "Frame.h"
#include "Graphics.h"
#include "UIMenuItemView.h"

#include <directxtk/SimpleMath.h>

UIStackingView::UIStackingView() :
	m_childViews(0),
	m_orientation(UIStackingView::Orientations::Horizontal),
	m_spacing(0)
{
}

UIStackingView::~UIStackingView()
{
	Shutdown();
}

void UIStackingView::Init(std::string name)
{
	m_name = name;
	m_spacing = 5;
	m_isActive = false;
}

void UIStackingView::Render(Graphics* graphics)
{
	for(UIMenuItemView* i : m_childViews)
	{
		i->Render(graphics);
	}
}

void UIStackingView::SetActive(bool isActive)
{
	m_isActive = isActive;

	for(UIMenuItemView* i : m_childViews)
	{
		i->SetActive(isActive);
	}
}

UIMenuItemView::SelectionStates UIStackingView::GetSelectionState(int index) const
{
	if(m_childViews.size() == 0 || index < 0 || index >= m_childViews.size()) 
		return UIMenuItemView::SelectionStates::Disabled;
	
	return m_childViews[index]->GetSelectionState();
}

void UIStackingView::SetOrientation(Orientations orientation)
{
	m_orientation = orientation;
}

void UIStackingView::SetSpacing(int spacing)
{
	m_spacing = spacing;
}

void UIStackingView::UpdateLayout(Frame frame)
{
	float running = m_orientation == Orientations::Horizontal ? (float)frame.x : (float)frame.y;
	
	for(UIMenuItemView* view : m_childViews)
	{
		int childHeight = view->GetHeight();
		int childWidth = view->GetWidth();

		float x = m_orientation == Orientations::Vertical ? (float)frame.x : running;
		float y = m_orientation == Orientations::Vertical ? running : (float)frame.y;

		view->SetPosition(Vector2(x, y));

		if(m_orientation == Orientations::Horizontal)
		{
			running += (childWidth + m_spacing);
		}
		else
		{
			running += (childHeight + m_spacing);
		}
	}
}

void UIStackingView::AddView(UIMenuItemView* uiView)
{
 	m_childViews.push_back(uiView);
}

void UIStackingView::Shutdown()
{
	for(UIMenuItemView* i : m_childViews)
	{
		delete i;
		i = nullptr;
	}

	m_childViews.clear();
}