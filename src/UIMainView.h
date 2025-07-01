#pragma once

#include "UIView.h"

#include <string>

class UIScreenFlashFX;
class Graphics;
class UIHudView;

class UIMainView : UIView
{
public:
	UIMainView();
	virtual ~UIMainView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override {};

	void Shutdown();

private:
	UIHudView* m_uiHudView;
	UIScreenFlashFX* m_screenFlashFX;
};