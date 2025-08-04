#include "UIOptionsView.h"

#include "AudioEngine.h"
#include "Frame.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Input.h"
#include "Logger.h"
#include "SettingsManager.h"
#include "UICycleMenuItemView.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UIPanelContainer.h"
#include "UISliderMenuItemView.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"
#include "UIView.h"
#include "Window.h"

#include <algorithm>
#include <cmath>
#include <DirectXColors.h>
#include <fmt/core.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace GameStateNameLibrary;
using namespace GlobalConstants;

UIOptionsView::UIOptionsView() :
	m_panelContainer(nullptr)
{
}

UIOptionsView::~UIOptionsView()
{
	Shutdown();
}

void UIOptionsView::Init(std::string name, Window* window, Graphics* graphics, Input* input)
{
	Logger::LogInfo("Initialising UI Options View.");

	m_window = window;
	m_graphics = graphics;
	m_name = name;

	m_panelContainer = new UIPanelContainer();
	m_panelContainer->Init("UI Panel", RECT{ 0, 0, 220, 90 });
	m_panelContainer->SetOverlayAlpha(1.0f);

	m_uiStackingView.Init("Options Menu Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	m_menuOptions.emplace_back(new OptionsMenuOption(
		"SFX Volume",
		nullptr,
		OptionType::SFXVolume,
		SelectionType::Slider,
		SetSFXVolume,
		GetSFXVolumeIndex));

	m_menuOptions.emplace_back(new OptionsMenuOption(
		"Music Volume",
		nullptr,
		OptionType::MusicVolume,
		SelectionType::Slider,
		SetMusicVolume,
		GetMusicVolumeIndex));

	m_menuOptions.emplace_back(new OptionsMenuOption(
		"Resolution",
		nullptr,
		OptionType::Resolution,
		SelectionType::Cycle,
		SetScreenResolution,
		GetScreenResolutionIndex));

	m_menuOptions.emplace_back(new OptionsMenuOption(
		"Fullscreen",
		nullptr,
		OptionType::Fullscreen,
		SelectionType::Cycle,
		SetFullscreen,
		GetFullscreenIndex));

	m_menuOptions.emplace_back(new OptionsMenuOption(
		"Back",
		Back,
		OptionType::None,
		SelectionType::Fixed,
		nullptr,
		nullptr));

	for(const auto& optionBase : m_menuOptions)
	{
		std::string name = optionBase->label;
		UIMenuItemView* item = nullptr;

		// Try to cast the base pointer to the richer OptionsMenuOption
		if(auto* option = dynamic_cast<OptionsMenuOption*>(optionBase))
		{
			switch(option->selectionType)
			{
				case SelectionType::Slider:
				{
					auto* sliderItem = new UISliderMenuItemView();
					sliderItem->Init(name, input, 1.0f, option->getDefaultValue(this), Colors::White.v, option->onIndexChange, this);
					item = sliderItem;
					break;
				}
				case SelectionType::Cycle:
				{
					auto* cycleItem = new UICycleMenuItemView();
					cycleItem->Init(name, input, GetOptionsForOptionType(option->optionType), option->getDefaultValue(this), option->onIndexChange, this);
					item = cycleItem;
					break;
				}
				default:
				{
					auto* textMenuItem = new UITextMenuItemView();
					textMenuItem->Init(name, input);
					textMenuItem->SetText(name);
					item = textMenuItem;
					break;
				}
			}
		}
		else
		{
			// Fallback: basic text item for non-options menus
			auto* textMenuItem = new UITextMenuItemView();
			textMenuItem->Init(name, input);
			textMenuItem->SetText(name);
			item = textMenuItem;
		}

		if(item)
		{
			item->SetSelectedStateColours(Colors::White.v, Colors::SlateGray.v, Colors::Black.v);
			item->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
			m_uiStackingView.AddView(item);
		}
	}

	auto options = m_uiStackingView.GetMenuItems();

	for(int i = 0; i < options.size(); i++)
	{
		int up = i == 0 ? -1 : i - 1;
		int down = i + 1;

		if(i == options.size() - 1)
		{
			down = -1;
		}

		UIMenuItemView::Navigation nav;
		nav.up = up;
		nav.down = down;
		nav.left = -1;
		nav.right = -1;

		options[i]->SetNavigation(nav);
	}

	Frame frame{};
	frame.x = 20;
	frame.y = 40;
	frame.width = (int)(GameWidth / 2.0f);
	frame.height = GameHeight;

	m_uiStackingView.UpdateLayout(frame);

	m_assignedStates.push_back("SharedOptions");

	UIManager::RegisterUIView(this);
}

void UIOptionsView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	UIMenuView::Render(graphics);

	if(GameStateManager::Instance()->GetPreviousState()->GetStateName() == Paused)
	{
		m_panelContainer->Render(graphics);
	}
}

void UIOptionsView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Options View");

	UIMenuView::Shutdown();
}

void UIOptionsView::TransitionIn(bool isAnimated)
{
	UIMenuView::TransitionIn(isAnimated);

	if(GameStateManager::Instance()->GetPreviousState()->GetStateName() == Paused)
		m_panelContainer->SetOverlayAlpha(1.0f);

	m_panelContainer->SetActive(true);
}

void UIOptionsView::TransitionOut(bool isAnimated)
{
	UIMenuView::TransitionOut(isAnimated);

	if(GameStateManager::Instance()->GetCurrentState()->GetStateName() == Paused)
		m_panelContainer->SetOverlayAlpha(1.0f);

	if(!isAnimated)	m_panelContainer->SetActive(false);
}

void UIOptionsView::OnCancelPressed()
{
	Back();
}

void UIOptionsView::DoTransition(float deltaTime)
{
	UIMenuView::DoTransition(deltaTime);

	m_panelContainer->SetPanelAlpha(m_lerpedAlpha);

	if(GameStateManager::Instance()->GetCurrentState()->GetStateName() == Paused||
		GameStateManager::Instance()->GetPreviousState()->GetStateName() == Paused) return;

	m_panelContainer->SetOverlayAlpha(m_lerpedAlpha);
}

void UIOptionsView::SetSFXVolume(UIMenuView* owner, int index)
{
	float value = index / SliderScaler;
	AudioEngine::Instance()->SetSFXVolume(value);
	SettingsManager::Instance()->SetSFXVolume(value);
	UIManager::PlayUISound(UISoundType::Select);
}

void UIOptionsView::SetMusicVolume(UIMenuView* owner, int index)
{
	float value = std::clamp(index / SliderScaler, 0.0f, 1.0f);
	AudioEngine::Instance()->SetMusicVolume(value);
	SettingsManager::Instance()->SetMusicVolume(value);
}

void UIOptionsView::SetScreenResolution(UIMenuView* owner, int index)
{
	std::vector<Graphics::DisplayMode> modes;
	Graphics::DisplayMode mode;

	modes = owner->GetGraphics()->GetSupportedResolutions();
	mode = modes[index];

	if(UIOptionsView::GetFullscreenIndex(owner) == 0)
	{
		owner->GetWindow()->ResizeWindow(mode.width, mode.height);
	}

	owner->GetGraphics()->SetResolution(mode.width, mode.height);
	
	SettingsManager::Instance()->SetScreenWidth(mode.width);
	SettingsManager::Instance()->SetScreenHeight(mode.height);
	owner->GetWindow()->SetFullscreen(SettingsManager::Instance()->IsFullscreen());

	UIManager::PlayUISound(UISoundType::Select);
}

void UIOptionsView::SetFullscreen(UIMenuView* owner, int index)
{
	owner->GetWindow()->SetFullscreen(index);
	SettingsManager::Instance()->SetFullscreen(index);
}

void UIOptionsView::Back()
{
	SettingsManager::Instance()->Save();
	GameStateManager::Instance()->ProceedToPreviousState();
}

std::vector<std::string> UIOptionsView::GetOptionsForOptionType(OptionType optionType)
{
	switch(optionType)
	{
	case UIOptionsView::OptionType::Resolution :
	{
		std::vector<Graphics::DisplayMode> modes = m_graphics->GetSupportedResolutions();
		std::vector<std::string> resolutions;

		for(auto& it : modes)
		{
			std::string entry;
			entry = fmt::format("  {0} x {1}  ", it.width, it.height);
			if(entry.length() % 2 == 0) entry = " " + entry + "  ";
			resolutions.push_back(entry);
		}

		return resolutions;
	}
	case UIOptionsView::OptionType::Fullscreen :
	{
		std::vector<std::string> modes =
		{
			" WINDOWED ",
			" FULLSCREEN "
		};
		return modes;
	}
	default:
		break;
	}

	return std::vector<std::string>();
}

int UIOptionsView::GetSFXVolumeIndex(UIMenuView* owner)
{
	float volume = AudioEngine::Instance()->GetSFXVolume();
	return static_cast<int>(std::ceil (volume * SliderScaler));
}

int UIOptionsView::GetMusicVolumeIndex(UIMenuView* owner)
{
	float volume = AudioEngine::Instance()->GetMusicVolume();
	return static_cast<int>(std::ceil(volume * SliderScaler));
}

int UIOptionsView::GetScreenResolutionIndex(UIMenuView* owner)
{
	int width;
	int height;
	std::vector<Graphics::DisplayMode> modes;
;
	width = owner->GetGraphics()->GetOutputWidth();
	height = owner->GetGraphics()->GetOutputHeight();
	modes = owner->GetGraphics()->GetSupportedResolutions();

	for(int i = 0; i < modes.size(); i++)
	{
		Graphics::DisplayMode mode;
		mode = modes[i];
		if(mode.width == width && mode.height == height) return i;
	}

	return 0;
}

int UIOptionsView::GetFullscreenIndex(UIMenuView* owner)
{
	return owner->GetWindow()->GetFullscreen();
}