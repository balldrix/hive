#pragma once

#include "UIView.h"
#include "UIStackingView.h"

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

protected:
	void DoTransition(float deltaTime) override;

private:

	std::string m_menuItems[3] =
	{
		"Start",
		"Options",
		"Quit"
	};

	UIStackingView m_uiStackingView;
	float m_startingAlpha;
	float m_targetAlpha;
};