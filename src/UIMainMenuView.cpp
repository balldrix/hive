#include "UIMainMenuView.h"

#include "Frame.h"
#include "GlobalConstants.h"
#include "LoadingGameState.h"
#include "Logger.h"
#include "MenuSystem.h"
#include "UIManager.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <string>

using namespace GlobalConstants;

static const float TransitionInDuration = 0.6f;
static const float TransitionOutDuration = 0.8f;

UIMainMenuView::UIMainMenuView() :
	m_startingAlpha(0.0f),
	m_targetAlpha(0.0f)
{
}

UIMainMenuView::~UIMainMenuView()
{
	Shutdown();
}

void UIMainMenuView::Init(std::string name)
{
	m_name = name;
	m_uiStackingView.Init("Main Menu Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	for(const auto& option : m_menuOptions)
	{
		std::string name = option.name;
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(name);
		item->SetText(name);
		item->SetSelectedStateColours(Colors::White.v, Colors::SlateGray.v, Colors::Black.v);
		m_uiStackingView.AddView(item);
	}

	auto options = m_uiStackingView.GetMenuItems();

	for (int i = 0; i < options.size(); i++)
	{
		int up = i == 0 ? -1 : i - 1;
		int down = i + 1;

		if (i == options.size() - 1)
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

	MenuSystem::SetMenuItems(this, m_uiStackingView.GetMenuItems());
	UIManager::RegisterUIView(this);
}

void UIMainMenuView::Update(float deltaTime)
{
	if(!m_isActive) return;

	switch (m_currentViewState)
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

void UIMainMenuView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_uiStackingView.Render(graphics);
}

void UIMainMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Main Menu View");

	UIManager::UnregisterUIView(this);
}

void UIMainMenuView::TransitionIn(bool isAnimated)
{
	if(m_currentViewState == ViewStates::AnimatingIn || 
		m_currentViewState == ViewStates::Visible) return;

	m_isActive = true;
	m_uiStackingView.SetActive(true);
	m_currentViewState = ViewStates::AnimatingIn;
	m_transitionTimer = TransitionInDuration;
	m_startingAlpha = 0.0f;
	m_targetAlpha = 1.0f;
}

void UIMainMenuView::TransitionOut(bool isAnimated)
{
	if(m_currentViewState == ViewStates::AnimatingOut || 
		m_currentViewState == ViewStates::NotVisible) return;

	m_currentViewState = ViewStates::AnimatingOut;
	m_transitionTimer = TransitionOutDuration;
	m_startingAlpha = 1.0f;
	m_targetAlpha = 0.0f;
}

void UIMainMenuView::OnConfirmPressed(int selectedIndex)
{
	if(selectedIndex >= 0 && selectedIndex < MaxOptions)
	{
		Logger::LogInfo(fmt::format("Calling OnConfirmPressed on {} functon", m_menuOptions[selectedIndex].name));

		(this->*m_menuOptions[selectedIndex].function)();
		return;
	}

	Logger::LogError(fmt::format("Calling OnConfirmPressed has no menu entry with index {}", selectedIndex));
}

void UIMainMenuView::DoTransition(float deltaTime)
{
	if(m_transitionTimer > 0)
	{
		float duration = m_currentViewState == ViewStates::AnimatingIn ? TransitionInDuration : TransitionOutDuration;
		float t = m_transitionTimer / duration;
		float lerpedAlpha = std::lerp(m_startingAlpha, m_targetAlpha, 1 - t);
		
		for(UIView* uiView : m_uiStackingView.GetMenuItems())
		{
			Color colour = uiView->GetColour();
			colour.A(lerpedAlpha);
			uiView->SetColour(colour);
		}
		
		m_transitionTimer -= deltaTime;		
		return;
	}

	switch (m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		break;
	case UIView::ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
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

void UIMainMenuView::OnCancelPressed()
{
}

bool UIMainMenuView::IsMenuItemSelectionAllowed(Vector2 direction, int index)
{
	return m_uiStackingView.GetSelectionState(index) != UIMenuItemView::SelectionStates::Disabled;
}

void UIMainMenuView::HandleMenuItemSelection(int index)
{
}

void UIMainMenuView::StartGame()
{
	Logger::LogInfo("Starting Game");

	LoadingGameState::ProceedToGameplay();
}

void UIMainMenuView::ProceedToOptions()
{
}

void UIMainMenuView::QuitGame()
{
	PostQuitMessage(0);
}