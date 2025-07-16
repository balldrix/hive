#pragma once

#include "UIMenuView.h"

#include <string>

class Graphics;

class UIPauseMenuView : public UIMenuView
{
public:
	UIPauseMenuView();
	virtual ~UIPauseMenuView();

	void Init(std::string name) override;
	void Shutdown() override;

	void OnCancelPressed() override;
	
private:
	static void Continue();
	static void ProceedToOptionsView();
	static void ShowQuitToMenuPrompt();
	static void ShowQuitToDesktopPrompt();
};