#pragma once

#include "UIMenuView.h"

#include <string>

class GameStateManager;
class Input;

class UIMainMenuView : public UIMenuView
{
public:
	UIMainMenuView();
	virtual ~UIMainMenuView();

	void Init(std::string name, Input* input);
	virtual void Shutdown() override;

	void OnCancelPressed() override {};

private:
	static void StartGame();
	static void ProceedToOptions();
	static void QuitGame();
};