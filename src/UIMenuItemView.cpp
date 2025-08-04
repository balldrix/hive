#include "UIMenuItemView.h"

#include "Input.h"
#include "MenuSystem.h"

#include <directxtk/SimpleMath.h>

static const float HoldDelay = 0.4f;
static const float RepeatRate = 0.1f;

UIMenuItemView::UIMenuItemView() :
	m_selectionState(SelectionStates::Disabled),
	m_holdTimer(0.0f),
	m_repeatTimer(0.0f),
	m_buttonPressed(false),
	m_selectedIndex(0),
	m_input(nullptr),
	m_owner(nullptr)
{
}

void UIMenuItemView::Init(Input* input)
{
	m_input = input;
}

void UIMenuItemView::Update(float deltaTime)
{
	if(!m_isActive) return;

	if(m_selectionState != SelectionStates::Selected || !MenuSystem::IsInputAllowed())
	{
		m_buttonPressed = false;
		m_holdTimer = 0.0f;
		return;
	}

	auto gamePadState = m_input->GetGamePadState();
	auto buttons = m_input->GetGamePadButtons();

	if(m_input->WasKeyPressed(PLAYER_RIGHT_KEY) || m_input->WasGamePadButtonPressed(buttons.dpadRight) || m_input->WasGamePadButtonPressed(buttons.leftStickRight))
	{
		SelectNextOption();
		m_buttonPressed = true;
		m_holdTimer = 0.0f;
		m_repeatTimer = 0.0f;
	}
	else if(m_input->WasKeyPressed(PLAYER_LEFT_KEY) || m_input->WasGamePadButtonPressed(buttons.dpadLeft) || m_input->WasGamePadButtonPressed(buttons.leftStickLeft))
	{
		SelectPreviousOption();
		m_buttonPressed = true;
		m_holdTimer = 0.0f;
		m_repeatTimer = 0.0f;
	}
	else if(m_buttonPressed && (m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight()))
	{
		if(m_holdTimer < HoldDelay)
		{
			m_holdTimer += deltaTime;
		}
		else
		{
			m_repeatTimer += deltaTime;

			if (m_repeatTimer >= RepeatRate)
			{
				SelectNextOption();
				m_repeatTimer = 0.0f;
			}
		}
	}
	else if(m_buttonPressed && (m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft()))
	{
		if (m_holdTimer < HoldDelay)
		{
			m_holdTimer += deltaTime;
		}
		else
		{
			m_repeatTimer += deltaTime;

			if (m_repeatTimer >= RepeatRate)
			{
				SelectPreviousOption();
				m_repeatTimer = 0.0f;
			}
		}
	}
	else
	{
		m_buttonPressed = false;
		m_holdTimer = 0.0f;
		m_repeatTimer = 0.0f;
	}
}

void UIMenuItemView::ChangeSelectionState(SelectionStates selectedState)
{
	SelectionStates previous = m_selectionState;
	m_selectionState = selectedState;
	HandleSelectionStateChanged(previous, selectedState);
}

void UIMenuItemView::SetSelectedStateColours(Color selected, Color unselected, Color disabled)
{
	m_selectedTextColour = selected;
	m_unselectedTextColour = unselected;
	m_disabledTextColour = disabled;

	m_selectionStateColours =
	{
		{ UIMenuItemView::SelectionStates::Selected, m_selectedTextColour },
		{ UIMenuItemView::SelectionStates::UnSelected, m_unselectedTextColour },
		{ UIMenuItemView::SelectionStates::Disabled, m_disabledTextColour }
	};
}

void UIMenuItemView::SetNavigation(Navigation navigation)
{
	m_navigation = navigation;
}

void UIMenuItemView::SelectNextOption()
{
	m_selectedIndex++;
	HandleOptionChange(m_selectedIndex);
}

void UIMenuItemView::SelectPreviousOption()
{
	m_selectedIndex--;
	HandleOptionChange(m_selectedIndex);
}