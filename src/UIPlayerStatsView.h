#pragma once

#include "UIView.h"
#include <string>

class Graphics;
class UIBarView;
class UIKillCount;
class UIPortraitView;

class UIPlayerStatsView : public UIView
{
public:
	UIPlayerStatsView();
	~UIPlayerStatsView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override {}

	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;
	void ForceHide(bool isForced) override;

	void Shutdown() override;
private:
	void DoTransition(float deltaTime);

	UIPortraitView* m_portraitView;
	UIBarView* m_healthBar;
	UIBarView* m_specialBar;
	UIKillCount* m_killCount;
};