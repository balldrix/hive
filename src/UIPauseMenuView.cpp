#include "UIPauseMenuView.h"

#include "Frame.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "Logger.h"
#include "UIManager.h"
#include "UIMenuItemView.h"
#include "UIMenuView.h"
#include "UIStackingView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <string>
#include <vector>

using namespace GlobalConstants;

UIPauseMenuView::UIPauseMenuView()
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

	m_assignedStates.push_back("Pause");

	UIManager::RegisterUIView(this);
}

void UIPauseMenuView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Pause Menu View.");
	UIMenuView::Shutdown();
}

void UIPauseMenuView::OnCancelPressed()
{
	Continue();
}

void UIPauseMenuView::Continue()
{
	GameStateManager::Instance()->SwitchState("Gameplay");
}

void UIPauseMenuView::ProceedToOptionsView()
{
	GameStateManager::Instance()->SwitchState("SharedOptions");
}

void UIPauseMenuView::ShowQuitToMenuPrompt()
{
	// @TODO: Show Quit Prompt
}

void UIPauseMenuView::ShowQuitToDesktopPrompt()
{
	// @TODO Show Quit Prompt
}
