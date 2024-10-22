#pragma once

#include "UIView.h"
#include "UIStackingView.h"

class UIIMainMenuView : public UIView
{
public:
	UIIMainMenuView() {};
	virtual ~UIIMainMenuView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void TransitionIn(bool isAnimated) override;
	void TransitionOut(bool isAnimated) override;

protected:
	void DoTransition(float deltaTime) override;

private:

	std::string m_menuItems[4] =
	{
		"Start",
		"Options",
		"Quit"
	};

	UIStackingView m_uiStackingView;
};