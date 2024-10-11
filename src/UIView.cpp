#include "UIView.h"

UIView::UIView() :
	m_assignedStates(0),
	m_isAnimating(false),
	m_transitionTimer(0.0f),
	m_isActive(false)
{
}

void UIView::SetActive(bool isActive)
{
	m_isActive = isActive;
}

void UIView::AssignState(std::string stateName)
{
	m_assignedStates.push_back(stateName);
}
