#pragma once

#include "UIMenuView.h"

#include <string>

class Graphics;
class Input;
class UIImageView;
class UIPanelContainer;
class UISpriteText;
class UIPromptView;

class UIPauseMenuView : public UIMenuView
{
public:
	UIPauseMenuView();
	virtual ~UIPauseMenuView();

	void Init(std::string name, Input* input);
	void Render(Graphics* graphcs) override;
	void Update(float deltaTime) override;
	void Shutdown() override;

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

	void OnConfirmPressed(int selectedIndex) override;
	void OnCancelPressed() override;

	virtual void Focus();

protected:
	void DoTransition(float deltaTime) override;

private:
	static void Continue(UIMenuView* owner);
	static void ProceedToOptionsView(UIMenuView* owner);
	static void ShowQuitToMenuPrompt(UIMenuView* owner);
	static void ShowQuitToDesktopPrompt(UIMenuView* owner);

	UIPanelContainer* m_panelContainer;
	UIPromptView* m_quitPrompt;
};