#include "UISliderMenuItemView.h"

#include "AssetLoader.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "MenuSystem.h"
#include "UIBarView.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UITextMenuItemView.h"

#include <algorithm>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

static const float HoldDelay = 0.4f;
static const float RepeatRate = 0.1f;

UISliderMenuItemView::UISliderMenuItemView() :
	m_sliderBar(nullptr),
	m_holdTimer(0.0f),
	m_repeatTimer(0.0f),
	m_buttonPressed(false),
	m_maxValue(0.0f)
{
}

UISliderMenuItemView::~UISliderMenuItemView()
{
	delete m_sliderBar;
	m_sliderBar = nullptr;
}

void UISliderMenuItemView::Init(std::string name, float max, int defaultValue, Color colour, void (*delegate)(int))
{
	UITextMenuItemView::Init(name);
	UITextMenuItemView::SetText(name);

	m_maxValue = max;
	m_selectedIndex = defaultValue;
	m_sliderBar = new UIBarView();
	m_sliderBar->Init(fmt::format("{}_slider", name));
	m_sliderBar->SetCurrentValue(defaultValue / SliderScaler);
	m_sliderBar->SetMaxValue(max);
	m_sliderBar->SetFillTexture(AssetLoader::GetTexture("t_pixel"));
	m_sliderBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_sliderBar->SetBackgroundColour(Colors::SlateGray.v);
	m_sliderBar->SetWidth(100);
	m_sliderBar->SetHeight(GetHeight());
	m_sliderBar->SetActive(true);
	m_sliderBar->SetDepth(0.5f);
	onSliderChanged = delegate;
}

void UISliderMenuItemView::SetPosition(const Vector2& position)
{
	UITextMenuItemView::SetPosition(position);
	m_sliderBar->SetPosition(Vector2(104.0f, position.y));
}

void UISliderMenuItemView::SetColour(Color colour)
{
	UITextMenuItemView::SetColour(colour);
	m_sliderBar->SetAlpha(colour.A());
}

void UISliderMenuItemView::Update(float deltaTime)
{
	if(!m_isActive) return;

	m_sliderBar->Update(deltaTime);

	if(m_selectionState != SelectionStates::Selected || !MenuSystem::IsInputAllowed())
	{
		m_buttonPressed = false;
		m_holdTimer = 0.0f;
		return;
	}

	Input* input = GameStateManager::Instance()->GetInput();
	auto gamePadState = input->GetGamePadState();
	auto buttons = input->GetGamePadButtons();

	if(input->WasKeyPressed(PLAYER_RIGHT_KEY) || input->WasGamePadButtonPressed(buttons.dpadRight) || input->WasGamePadButtonPressed(buttons.leftStickRight))
	{
		SelectNextOption();
		m_buttonPressed = true;
		m_holdTimer = 0.0f;
		m_repeatTimer = 0.0f;
	}
	else if(input->WasKeyPressed(PLAYER_LEFT_KEY) || input->WasGamePadButtonPressed(buttons.dpadLeft) || input->WasGamePadButtonPressed(buttons.leftStickLeft))
	{
		SelectPreviousOption();
		m_buttonPressed = true;
		m_holdTimer = 0.0f;
		m_repeatTimer = 0.0f;
	}
	else if(m_buttonPressed && (input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight()))
	{
		if(m_holdTimer < HoldDelay)
		{
			m_holdTimer += deltaTime;
		}
		else
		{
			m_repeatTimer += deltaTime;

			if(m_repeatTimer >= RepeatRate)
			{
				SelectNextOption();
				m_repeatTimer = 0.0f;
			}
		}
	}
	else if(m_buttonPressed && (input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft()))
	{
		if(m_holdTimer < HoldDelay)
		{
			m_holdTimer += deltaTime;
		}
		else
		{
			m_repeatTimer += deltaTime;

			if(m_repeatTimer >= RepeatRate)
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

void UISliderMenuItemView::Render(Graphics* graphics)
{
	UITextMenuItemView::Render(graphics);
	m_sliderBar->Render(graphics);
}

void UISliderMenuItemView::SelectNextOption()
{
	m_selectedIndex++;
	HandleOptionChange(m_selectedIndex);
}

void UISliderMenuItemView::SelectPreviousOption()
{
	m_selectedIndex--;
	HandleOptionChange(m_selectedIndex);
}

void UISliderMenuItemView::HandleOptionChange(int index)
{
	m_selectedIndex = std::clamp(index, 0, (int)(m_maxValue * SliderScaler));
	m_sliderBar->SetCurrentValue(m_maxValue / SliderScaler * m_selectedIndex);

	if(onSliderChanged) onSliderChanged(index);
}
