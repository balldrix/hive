#pragma once

#include "UIView.h"
#include <string>

class Graphics;
class UIPlayerStatsView;

class UIHudView : public UIView
{
public:
	UIHudView();
	virtual ~UIHudView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	void Shutdown();

private:
	UIPlayerStatsView* m_playerInfoView;
};