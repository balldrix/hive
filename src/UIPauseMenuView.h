#pragma once

#include "UIMenuView.h"

#include <string>

class Graphics;
class Input;
class UIImageView;
class UIPanelContainer;
class UISpriteText;

class UIPauseMenuView : public UIMenuView
{
public:
	UIPauseMenuView();
	virtual ~UIPauseMenuView();

	void Init(std::string name, Input* input);
	void Render(Graphics* graphcs) override;
	void Shutdown() override;

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

	void OnCancelPressed() override;
	
protected:
	void DoTransition(float deltaTime) override;

private:
	static void Continue();
	static void ProceedToOptionsView();
	static void ShowQuitToMenuPrompt();
	static void ShowQuitToDesktopPrompt();

	UIPanelContainer* m_panelContainer;
	UISpriteText* m_titleText;
};