#pragma once

#include "IMenuSystemInteraction.h"
#include "UIStackingView.h"
#include "UIView.h"

#include <string>

class UIMainMenuView : public UIView, IMenuSystemInteraction
{
public:
	UIMainMenuView();
	virtual ~UIMainMenuView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

	void OnConfirmPressed(int selectedIndex) override;
	void OnCancelPressed() override;
	bool IsMenuItemSelectionAllowed(Vector2 direction, int index) override;
	void HandleMenuItemSelection(int index) override;

protected:
	void DoTransition(float deltaTime) override;

private:
	static constexpr int MaxOptions = 3;

	struct MenuOption
	{
		std::string name;
		void(UIMainMenuView::*function)();
	};

	void StartGame();
	void ProceedToOptions();
	void QuitGame();

	MenuOption m_menuOptions[MaxOptions] =
	{
		{ "Start", &UIMainMenuView::StartGame },
		{ "Options", &UIMainMenuView::ProceedToOptions },
		{ "Quit", &UIMainMenuView::QuitGame }
	};

	UIStackingView m_uiStackingView;
};