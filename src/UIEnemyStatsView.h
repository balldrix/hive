#pragma once

#include "UIView.h"
#include <string>

class UIBarView;
class UIPortraitView;

class UIEnemyStatsView : public UIView
{
public:
	UIEnemyStatsView();
	~UIEnemyStatsView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	void Shutdown() override;

private:
	UIPortraitView* m_portraitView;
	UIBarView* m_healthBar;
};

