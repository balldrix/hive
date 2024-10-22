#include "UIMenuItemView.h"

UIMenuItemView::UIMenuItemView() :
	m_currentSelectedState(SelectedStates::Disabled),
	onSelected(nullptr)
{
}

UIMenuItemView::~UIMenuItemView()
{
	onSelected = nullptr;
}

void UIMenuItemView::AddOnSelectedListener(void(*onSelected)())
{
	this->onSelected = onSelected;
}

void UIMenuItemView::OnSelect()
{
	onSelected();
}