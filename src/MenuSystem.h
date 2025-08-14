#pragma once

#include <vector>

#include "UIMenuItemView.h"

class Input;
class IMenuSystemInteraction;

class MenuSystem
{
public:
	static void Init(Input* input);
	static void Update();
	static void Destroy();

	static int GetSelectedIndex() { return s_selectedItemIndex; }

	static void SetSetSelectedIndex(int index);
	static void SetMenuItems(IMenuSystemInteraction* currentMenu, std::vector<UIMenuItemView*> menuItems);

	static void EnableInput();
	static void DisableInput();
	static bool IsInputAllowed() { return s_isInputAllowed; }


private:
	MenuSystem();
	~MenuSystem();

	static void SelectIndex(int index);
	static void SelectNextPossibleIndex(int index, Vector2 direction, int counter = 0);

	void Shutdown();
	
	static MenuSystem* s_instance;
	static std::vector<UIMenuItemView*> s_menuItems;
	static bool s_isInputAllowed;
	static int s_selectedItemIndex;
	static IMenuSystemInteraction* s_currentMenu;
	Input* m_input;
};

