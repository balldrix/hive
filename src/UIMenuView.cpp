#include "UIMenuView.h"

#include "Graphics.h"
#include "Logger.h"
#include "MenuSystem.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UIView.h"

#include <cmath>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>

UIMenuView::UIMenuView() :
	m_window(nullptr),
	m_graphics(nullptr),
	m_lerpedAlpha(0.0f),
	m_previousSelectedIndex(0)
{
}

void UIMenuView::Update(float deltaTime)
{
	if(!m_isActive) return;

	for(UIMenuItemView* item : m_uiStackingView.GetMenuItems())
	{
		item->Update(deltaTime);
	}

	switch(m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		m_uiStackingView.SetActive(false);
		m_isActive = false;
		m_isAnimating = false;
		break;
	case UIView::ViewStates::AnimatingIn:
		DoTransition(deltaTime);
		break;
	case UIView::ViewStates::Visible:
		m_isAnimating = false;
		break;
	case UIView::ViewStates::AnimatingOut:
		DoTransition(deltaTime);
		break;
	default:
		break;
	}
}

void UIMenuView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_uiStackingView.Render(graphics);
}

void UIMenuView::Shutdown()
{
	for(auto& option : m_menuOptions)
	{
		delete option;
		option = nullptr;
	}

	UIManager::UnregisterUIView(this);
}

void UIMenuView::TransitionIn(bool isAnimated)
{
	m_hasPlayedTransitionSound = false;
	m_isActive = true;
	MenuSystem::DisableInput();

	if(m_currentViewState == ViewStates::AnimatingIn ||
		m_currentViewState == ViewStates::Visible) return;

	m_isAnimating = true;
	m_uiStackingView.SetActive(true);
	m_currentViewState = ViewStates::AnimatingIn;
	m_transitionTimer = TransitionInDuration;
	m_startingAlpha = 0.0f;
	m_targetAlpha = 1.0f;
}

void UIMenuView::TransitionOut(bool isAnimated)
{
	m_hasPlayedTransitionSound = false;
	for(UIMenuItemView* item : m_uiStackingView.GetMenuItems())
	{
		item->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
	}

	if(!isAnimated)
	{
		m_isActive = false;
		m_isAnimating = false;
		m_uiStackingView.SetActive(false);

		for(UIView* uiView : m_uiStackingView.GetMenuItems())
		{
			uiView->SetAlpha(0.0f);
		}

		m_currentViewState = ViewStates::NotVisible;
		return;
	}

	MenuSystem::DisableInput();

	if(m_currentViewState == ViewStates::AnimatingOut ||
		m_currentViewState == ViewStates::NotVisible) return;

	m_isAnimating = true;
	m_currentViewState = ViewStates::AnimatingOut;
	m_transitionTimer = TransitionOutDuration;
	m_startingAlpha = 1.0f;
	m_targetAlpha = 0.0f;
}

void UIMenuView::OnConfirmPressed(int selectedIndex)
{
	if(selectedIndex >= 0 && selectedIndex < m_menuOptions.size())
	{
		const auto& selectedOption = m_menuOptions[selectedIndex];
		Logger::LogInfo(fmt::format("Calling OnConfirmPressed on {} functon", selectedOption->label));
		selectedOption->OnConfirm(this);
		return;
	}

	Logger::LogError(fmt::format("Calling OnConfirmPressed has no menu entry with index {}", selectedIndex));
}

bool UIMenuView::IsMenuItemSelectionAllowed(Vector2 direction, int index)
{
	return m_uiStackingView.GetSelectionState(index) != UIMenuItemView::SelectionStates::Disabled;
}

void UIMenuView::DoTransition(float deltaTime)
{
	if(!m_hasPlayedTransitionSound && m_currentViewState == ViewStates::AnimatingIn)
	{
		UIManager::PlayUISound(UISoundType::Open);
		m_hasPlayedTransitionSound = true;
	}

	if(!m_hasPlayedTransitionSound && m_currentViewState == ViewStates::AnimatingOut)
	{
		UIManager::PlayUISound(UISoundType::Close);
		m_hasPlayedTransitionSound = true;
	}

	if(m_transitionTimer > 0)
	{
		float duration = m_currentViewState == ViewStates::AnimatingIn ? TransitionInDuration : TransitionOutDuration;
		float t = m_transitionTimer / duration;
		m_lerpedAlpha = std::lerp(m_startingAlpha, m_targetAlpha, 1 - t);

		for(UIView* uiView : m_uiStackingView.GetMenuItems())
		{
			uiView->SetAlpha(m_lerpedAlpha);
		}

		m_transitionTimer -= deltaTime;
		return;
	}

	switch(m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		break;
	case UIView::ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
		MenuSystem::SetMenuItems(this, m_uiStackingView.GetMenuItems());
		MenuSystem::EnableInput();
		break;
	case UIView::ViewStates::Visible:
		break;
	case UIView::ViewStates::AnimatingOut:
		m_currentViewState = ViewStates::NotVisible;
		m_isActive = false;
		break;
	default:
		break;
	}
}
