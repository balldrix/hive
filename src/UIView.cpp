#include "UIView.h"

UIView::UIView() :
	m_assignedStates(0),
	m_isAnimating(false),
	m_transitionTimer(0.0f),
	m_isActive(false),
	m_currentViewState(ViewStates::NotVisible),
	m_isForcedHidden(false),
	m_startingAlpha(0.0f),
	m_targetAlpha(0.0f)
{
}

void UIView::SetActive(bool isActive)
{
	m_isActive = isActive;
}

void UIView::ForceHide(bool isForced)
{
	m_isForcedHidden = isForced;
}

void UIView::AssignState(std::string stateName)
{
	m_assignedStates.push_back(stateName);
}