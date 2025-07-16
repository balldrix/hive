#pragma once

#include "UIMenuView.h"

#include <string>

class UIMainMenuView : public UIMenuView
{
public:
	UIMainMenuView();
	virtual ~UIMainMenuView();

	void Init(std::string name) override;
	virtual void Shutdown() override;

	void OnCancelPressed() override {};

private:

	static void StartGame();
	static void ProceedToOptions();
	static void QuitGame();
};