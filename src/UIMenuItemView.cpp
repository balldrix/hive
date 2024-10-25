#include "UIMenuItemView.h"

UIMenuItemView::UIMenuItemView() :
	m_selectionState(SelectionStates::Disabled)
{
}

void UIMenuItemView::SetNavigation(Navigation navigation)
{
	m_navigation = navigation;
}
