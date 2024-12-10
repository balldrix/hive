#pragma once

#include "UIView.h"
#include <string>

class Graphics;
class UIPlayerInfoView;

class UIHudView : public UIView
{
public:
	UIHudView();
	virtual ~UIHudView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	void Shutdown();

private:
	UIPlayerInfoView* m_playerInfoView;
};