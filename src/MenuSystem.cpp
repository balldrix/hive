#include "MenuSystem.h"

#include "Logger.h"
#include "Input.h"

MenuSystem* MenuSystem::s_instance = nullptr;
std::vector<UIMenuItemView*> MenuSystem::s_menuItems = {};
bool MenuSystem::s_isInputAllowed = false;
int MenuSystem::s_selectedItemIndex = 0;
UIView* MenuSystem::s_currentView = nullptr;

MenuSystem::~MenuSystem()
{
	Shutdown();
}

void MenuSystem::Init()
{
	Logger::LogInfo("Initialising Menu System");

	s_instance = new MenuSystem;
}

void MenuSystem::Update(Input* input)
{
	if(!s_instance->s_isInputAllowed) return;

	auto currentSelectedItem = s_instance->s_menuItems[s_selectedItemIndex];

	if(input->WasKeyPressed(ENTER_KEY))
	{
		currentSelectedItem->OnConfirmPressed();
		s_currentView->OnConfirmPressed(s_selectedItemIndex);
	}
}

void MenuSystem::Destroy()
{
	Logger::LogInfo("Shutting down Menu System");

	delete s_instance;
	s_instance = nullptr;
}

void MenuSystem::SetMenuItems(UIView* currentView, std::vector<UIMenuItemView*> menuItems)
{
	s_menuItems = menuItems;
	s_selectedItemIndex = 0;
	s_currentView = currentView;

	s_menuItems[s_selectedItemIndex]->ChangeSelectionState(UIMenuItemView::SelectionStates::Selected);
}

void MenuSystem::EnableInput()
{
	s_isInputAllowed = true;
}

void MenuSystem::DisableInput()
{
	s_isInputAllowed = false;
}

void MenuSystem::Shutdown()
{
	s_menuItems.clear();
}
