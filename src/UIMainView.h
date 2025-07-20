#pragma once

#include "UIView.h"

#include <string>

class Graphics;
class UIHudView;
class UIPauseMenuView;
class UIScreenFlashFX;

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
	UIPauseMenuView* m_uiPauseMenuView;
};