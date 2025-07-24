#include "UIPauseMenuView.h"

#include "Frame.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UIPanelContainer.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace GameStateNameLibrary;
using namespace GlobalConstants;

UIPauseMenuView::UIPauseMenuView() :
	m_panelContainer(nullptr),
	m_titleText(nullptr)
{
}

UIPauseMenuView::~UIPauseMenuView()
{
	Shutdown();
}

void UIPauseMenuView::Init(std::string name)
{
	Logger::LogInfo("Initialising UI Pause Menu View.");

	m_name = name;

	m_panelContainer = new UIPanelContainer();
	m_panelContainer->Init("UI Panel", RECT{ 0, 0, 150, 70 });

	m_uiStackingView.Init("Pause Menu Stacking View");
	m_uiStackingView.SetOrientation(UIStackingView::Orientations::Vertical);

	m_menuOptions.emplace_back(new MenuOptionBase("Continue", Continue));
	m_menuOptions.emplace_back(new MenuOptionBase("Options", ProceedToOptionsView));
	m_menuOptions.emplace_back(new MenuOptionBase("Quit To Menu", ShowQuitToMenuPrompt));
	m_menuOptions.emplace_back(new MenuOptionBase("Quit To Desktop", ShowQuitToDesktopPrompt));

	for(const auto& option : m_menuOptions)
	{
		std::string name = option->label;
		UITextMenuItemView* item = new UITextMenuItemView();
		item->Init(name);
		item->SetText(name);
		item->SetSelectedStateColours(Colors::White.v, Colors::SlateGray.v, Colors::Black.v);
		item->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
		m_uiStackingView.AddView(item);
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

	m_assignedStates.push_back("Paused");

	UIManager::RegisterUIView(this);
}

void UIPauseMenuView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	UIMenuView::Render(graphics);
	m_panelContainer->Render(graphics);
}

void UIPauseMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Pause Menu View.");

	UIMenuView::Shutdown();
}

void UIPauseMenuView::TransitionIn(bool isAnimated)
{
	UIMenuView::TransitionIn(isAnimated);

	if(GameStateManager::Instance()->GetPreviousState()->GetStateName() == SharedOptions)
		m_panelContainer->SetOverlayAlpha(1.0f);

	m_panelContainer->SetActive(true);
}

void UIPauseMenuView::TransitionOut(bool isAnimated)
{
	UIMenuView::TransitionOut(isAnimated);

	if(GameStateManager::Instance()->GetCurrentState()->GetStateName() == SharedOptions)
		m_panelContainer->SetOverlayAlpha(0.0f);

	if(!isAnimated)	m_panelContainer->SetActive(false);
}

void UIPauseMenuView::OnCancelPressed()
{
	Continue();
}

void UIPauseMenuView::DoTransition(float deltaTime)
{
	UIMenuView::DoTransition(deltaTime);

	m_panelContainer->SetPanelAlpha(m_lerpedAlpha);

	if(GameStateManager::Instance()->GetCurrentState()->GetStateName() == SharedOptions ||
		GameStateManager::Instance()->GetPreviousState()->GetStateName() == SharedOptions) return;
	m_panelContainer->SetOverlayAlpha(m_lerpedAlpha);
}

void UIPauseMenuView::Continue()
{
	GameStateManager::Instance()->SwitchState(Gameplay);
}

void UIPauseMenuView::ProceedToOptionsView()
{
	GameStateManager::Instance()->SwitchState(SharedOptions);
}

void UIPauseMenuView::ShowQuitToMenuPrompt()
{
	// @TODO: Show Quit Prompt
}

void UIPauseMenuView::ShowQuitToDesktopPrompt()
{
	// @TODO Show Quit Prompt
}
