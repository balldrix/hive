#pragma once

#include "UIView.h"

#include <directxtk/SimpleMath.h>
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
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override {}
	void Shutdown() override;

	void ForceHide(bool isForced) override;
	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;

private:
	void DoTransition(float deltaTime);

	UIPortraitView* m_portraitView;
	UIBarView* m_healthBar;
	UIBarView* m_specialBar;
	UIKillCount* m_killCount;

	Vector2 m_portraitViewStartPosition;
	Vector2 m_healthBarStartPosition;
	Vector2 m_specialBarStartPosition;
	Vector2 m_killCountStartPosition;
};