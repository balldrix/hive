#include "MenuSystem.h"

#include "IMenuSystemInteraction.h"
#include "Input.h"
#include "Logger.h"
#include "UIManager.h"
#include "UIMenuItemView.h"

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace DirectX;
using namespace SimpleMath;

MenuSystem* MenuSystem::s_instance = nullptr;
std::vector<UIMenuItemView*> MenuSystem::s_menuItems = {};
bool MenuSystem::s_isInputAllowed = false;
int MenuSystem::s_selectedItemIndex = 0;
IMenuSystemInteraction* MenuSystem::s_currentMenu = nullptr;

MenuSystem::~MenuSystem()
{
	Shutdown();
}

void MenuSystem::Init()
{
	Logger::LogInfo("Initialising Menu System.");

	s_instance = new MenuSystem;
}

void MenuSystem::Update(Input* input)
{
	if(!s_instance->s_isInputAllowed) return;

	auto currentSelectedItem = s_instance->s_menuItems[s_selectedItemIndex];
	auto buttons = input->GetGamePadButtons();

	if(input->WasKeyPressed(ENTER_KEY) || input->WasGamePadButtonPressed(buttons.a))
	{
		currentSelectedItem->OnConfirmPressed();
		s_currentMenu->OnConfirmPressed(s_selectedItemIndex);
		UIManager::PlayUISound(UISoundType::Select);
		return;
	}

	if(input->WasKeyPressed(ESC_KEY) || input->WasGamePadButtonPressed(buttons.b))
	{
		s_currentMenu->OnCancelPressed();
		UIManager::PlayUISound(UISoundType::Delete);
		return;
	}

	int index = -1;
	Vector2 direction = Vector2::Zero;

	if(input->WasKeyPressed(PLAYER_UP_KEY) || input->WasGamePadButtonPressed(buttons.dpadUp) || input->WasGamePadButtonPressed(buttons.leftStickUp))
	{
		index = currentSelectedItem->GetNavigation().up;
		direction = Vector2::UnitY;
	}
	else if(input->WasKeyPressed(PLAYER_DOWN_KEY) || input->WasGamePadButtonPressed(buttons.dpadDown) || input->WasGamePadButtonPressed(buttons.leftStickDown))
	{
		index = currentSelectedItem->GetNavigation().down;
		direction = -Vector2::UnitY;
	}
	else if(input->WasKeyPressed(PLAYER_LEFT_KEY) || input->WasGamePadButtonPressed(buttons.dpadLeft) || input->WasGamePadButtonPressed(buttons.leftStickLeft))
	{
		index = currentSelectedItem->GetNavigation().left;
		direction = Vector2::UnitX;
	}
	else if(input->WasKeyPressed(PLAYER_RIGHT_KEY) || input->WasGamePadButtonPressed(buttons.dpadRight) || input->WasGamePadButtonPressed(buttons.leftStickRight))
	{
		index = currentSelectedItem->GetNavigation().right;
		direction = -Vector2::UnitX;
	}

	if(direction == Vector2::Zero || s_currentMenu == nullptr) return;
	
	bool allowSelection = s_currentMenu->IsMenuItemSelectionAllowed(direction, index);

	if(allowSelection)
	{
		SelectIndex(index);
		return;
	}

	SelectNextPossibleIndex(index, direction);
}

void MenuSystem::SelectIndex(int index)
{
	if(index != -1 && index >= 0 && index < s_menuItems.size())
	{
		s_menuItems[s_selectedItemIndex]->ChangeSelectionState(UIMenuItemView::SelectionStates::UnSelected);
		s_menuItems[index]->ChangeSelectionState(UIMenuItemView::SelectionStates::Selected);
		s_selectedItemIndex = index;
		UIManager::PlayUISound(UISoundType::Navigate);
	}
}

void MenuSystem::SelectNextPossibleIndex(int index, Vector2 direction, int counter)
{
	int currentCount = counter;

	if(currentCount >= s_menuItems.size()) return;

	currentCount++;

	if(index == -1 || index < 0 || index >= s_menuItems.size()) return;

	UIMenuItemView::Navigation navigation = s_menuItems[index]->GetNavigation();
	int nextIndex = -1;

	if(direction == Vector2::UnitY)
	{
		nextIndex = navigation.up;
	}
	else if(direction == -Vector2::UnitY)
	{ 
		nextIndex = navigation.down;
	}
	else if(direction == Vector2::UnitX)
	{
		nextIndex = navigation.left;
	}
	else if(direction == -Vector2::UnitX)
	{
		nextIndex = navigation.right;
	}

	bool allowSelection = s_currentMenu->IsMenuItemSelectionAllowed(direction, nextIndex);

	if(allowSelection)
	{
		SelectIndex(nextIndex);
		return;
	}

	SelectNextPossibleIndex(nextIndex, direction, currentCount);
}

void MenuSystem::Destroy()
{
	Logger::LogInfo("Shutting down Menu System");

	delete s_instance;
	s_instance = nullptr;
}

void MenuSystem::SetMenuItems(IMenuSystemInteraction* currentMenu, std::vector<UIMenuItemView*> menuItems)
{
	s_menuItems = menuItems;
	s_selectedItemIndex = 0;
	s_currentMenu = currentMenu;
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
