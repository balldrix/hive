#pragma once

#include "UIView.h"
#include <string>

class Graphics;
class UIComboCounterView;
class UIEnemyStatsView;
class UIKillMilestoneView;
class UIPlayerStatsView;

class UIHudView : public UIView
{
public:
	UIHudView();
	virtual ~UIHudView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void ForceHide() override;
	void ForceShow() override;

	void Shutdown();

private:
	UIPlayerStatsView* m_playerStatsView;
	UIEnemyStatsView* m_enemyStatsView;
	UIComboCounterView* m_comboCounterView;
	UIKillMilestoneView* m_killMilestoneView;
};