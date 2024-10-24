#pragma once

#include "UIView.h"
#include "UIStackingView.h"

const int MaxOptions = 3;

class UIMainMenuView : public UIView
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

protected:
	void DoTransition(float deltaTime) override;

private:
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
	float m_startingAlpha;
	float m_targetAlpha;
};