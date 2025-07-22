#include "UIMainMenuView.h"

#include "Frame.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "GlobalConstants.h"
#include "LoadingGameState.h"
#include "Logger.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"
#include "UIView.h"

#include <DirectXColors.h>
#include <string>
#include <vector>
#include <Windows.h>

using namespace GameStateNameLibrary;
using namespace GlobalConstants;

UIMainMenuView::UIMainMenuView()
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

	m_menuOptions.emplace_back(new MenuOptionBase("Start", &UIMainMenuView::StartGame));
	m_menuOptions.emplace_back(new MenuOptionBase("Options", &UIMainMenuView::ProceedToOptions));
	m_menuOptions.emplace_back(new MenuOptionBase("Quit", &UIMainMenuView::QuitGame));

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

	UIManager::RegisterUIView(this);
}

void UIMainMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Main Menu View");

	UIMenuView::Shutdown();
}

void UIMainMenuView::StartGame()
{
	Logger::LogInfo("Starting Game");

	LoadingGameState::ProceedToGameplay();
}

void UIMainMenuView::ProceedToOptions()
{
	GameStateManager::Instance()->SwitchState(SharedOptions);
}

void UIMainMenuView::QuitGame()
{
	PostQuitMessage(0);
}