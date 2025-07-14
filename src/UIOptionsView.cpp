#include "UIOptionsView.h"

#include "AudioEngine.h"
#include "Frame.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "MenuSystem.h"
#include "SettingsManager.h"
#include "UICycleMenuItemView.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UISliderMenuItemView.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"
#include "UIView.h"
#include "Window.h"

#include <cmath>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace GlobalConstants;

UIOptionsView::UIOptionsView()
{
}

UIOptionsView::~UIOptionsView()
{
	Shutdown();
}

void UIOptionsView::Init(std::string name)
{
	Logger::LogInfo("Initialising UI Options View");

	m_name = name;
	m_uiStackingView.Init("Options Menu Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	for(const auto& option : m_menuOptions)
	{
		std::string name = option.label;
		UIMenuItemView* item = nullptr;

		switch(option.selectionType)
		{
		case UIOptionsView::SelectionType::Slider :
		{
			auto* sliderItem = new UISliderMenuItemView();
			sliderItem->Init(name, 1.0f, option.getDefaultValue(), Colors::White.v, option.onIndexChange);
			item = sliderItem;
		}
			break;
		case UIOptionsView::SelectionType::Cycle:
		{
			auto* cycleItem = new UICycleMenuItemView();
			cycleItem->Init(name, GetOptionsForOptionType(option.optionType), option.getDefaultValue(), option.onIndexChange);
			item = cycleItem;
			break;
		}
		default:
			auto* textMenuItem = new UITextMenuItemView();
			textMenuItem->Init(name);
			textMenuItem->SetText(name);
			item = textMenuItem;
			break;
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

	m_assignedStates.push_back("FrontEndOptions");
	m_assignedStates.push_back("IngameOptions");

	UIManager::RegisterUIView(this);
}

void UIOptionsView::Update(float deltaTime)
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

void UIOptionsView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_uiStackingView.Render(graphics);
}

void UIOptionsView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Options View");

	UIManager::UnregisterUIView(this);
}

void UIOptionsView::TransitionIn(bool isAnimated)
{
	m_hasPlayedTransitionSound = false;
	MenuSystem::DisableInput();

	if(m_currentViewState == ViewStates::AnimatingIn ||
		m_currentViewState == ViewStates::Visible) return;

	m_isActive = true;
	m_isAnimating = true;
	m_uiStackingView.SetActive(true);
	m_currentViewState = ViewStates::AnimatingIn;
	m_transitionTimer = TransitionInDuration;
	m_startingAlpha = 0.0f;
	m_targetAlpha = 1.0f;
}

void UIOptionsView::TransitionOut(bool isAnimated)
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

void UIOptionsView::OnConfirmPressed(int selectedIndex)
{
	if(selectedIndex >= 0 && selectedIndex < MaxOptions)
	{
		const auto& selectedOption = m_menuOptions[selectedIndex];
		if(selectedOption.onConfirm == nullptr) return;

		Logger::LogInfo(fmt::format("Calling OnConfirmPressed on {} functon", selectedOption.label));

		selectedOption.onConfirm();
		return;
	}

	Logger::LogError(fmt::format("Calling OnConfirmPressed has no menu entry with index {}", selectedIndex));
}

void UIOptionsView::OnCancelPressed()
{
	Back();
}

bool UIOptionsView::IsMenuItemSelectionAllowed(Vector2 direction, int index)
{
	return m_uiStackingView.GetSelectionState(index) != UIMenuItemView::SelectionStates::Disabled;
}

void UIOptionsView::HandleMenuItemSelection(int index)
{
}

void UIOptionsView::DoTransition(float deltaTime)
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
		float lerpedAlpha = std::lerp(m_startingAlpha, m_targetAlpha, 1 - t);


		for(UIView* uiView : m_uiStackingView.GetMenuItems())
		{
			uiView->SetAlpha(lerpedAlpha);
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

void UIOptionsView::SetSFXVolume(int index)
{
	float value = index / SliderScaler;
	AudioEngine::Instance()->SetSFXVolume(value);
	SettingsManager::Instance()->SetSFXVolume(value);
	UIManager::PlayUISound(UISoundType::Select);
}

void UIOptionsView::SetMusicVolume(int index)
{
	float value = index / SliderScaler;
	AudioEngine::Instance()->SetMusicVolume(value);
	SettingsManager::Instance()->SetMusicVolume(value);
}

void UIOptionsView::SetScreenResolution(int index)
{
	std::vector<Graphics::DisplayMode> modes;
	Graphics::DisplayMode mode;

	modes = GameStateManager::Instance()->GetGraphics()->GetSupportedResolutions();
	mode = modes[index];
	if(UIOptionsView::GetFullscreenIndex() == 0)
	{
		GameStateManager::Instance()->GetWindow()->ResizeWindow(mode.width, mode.height);
	}

	GameStateManager::Instance()->GetGraphics()->SetResolution(mode.width, mode.height);
	
	SettingsManager::Instance()->SetScreenWidth(mode.width);
	SettingsManager::Instance()->SetScreenHeight(mode.height);

	UIManager::PlayUISound(UISoundType::Select);
}

void UIOptionsView::SetFullscreen(int index)
{
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
		std::vector<Graphics::DisplayMode> modes = GameStateManager::Instance()->GetGraphics()->GetSupportedResolutions();
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

int UIOptionsView::GetSFXVolumeIndex()
{
	float volume = AudioEngine::Instance()->GetSFXVolume();
	return static_cast<int>(std::ceil (volume * SliderScaler));
}

int UIOptionsView::GetMusicVolumeIndex()
{
	float volume = AudioEngine::Instance()->GetMusicVolume();
	return static_cast<int>(std::ceil(volume * SliderScaler));
}

int UIOptionsView::GetScreenResolutionIndex()
{
	Graphics* graphics;
	int width;
	int height;
	std::vector<Graphics::DisplayMode> modes;

	graphics = GameStateManager::Instance()->GetGraphics();
	width = graphics->GetOutputWidth();
	height = graphics->GetOutputHeight();
	modes = graphics->GetSupportedResolutions();

	for(int i = 0; i < modes.size(); i++)
	{
		Graphics::DisplayMode mode;
		mode = modes[i];
		if(mode.width == width && mode.height == height) return i;
	}

	return 0;
}

int UIOptionsView::GetFullscreenIndex()
{
	return 0;
}