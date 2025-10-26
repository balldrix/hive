#pragma once

#include "UIView.h"

#include <string>

class Graphics;
class Input;
class UIHudView;
class UIPauseMenuView;
class UIScreenFlashFX;

class UIMainView : UIView
{
public:
	UIMainView();
	virtual ~UIMainView();

	void Init(std::string name, Input* input);
	void Render(Graphics* graphics) override {};
	UIHudView* GetUIHudView() const { return m_uiHudView; }
	void Shutdown();

private:
	UIHudView* m_uiHudView;
	UIScreenFlashFX* m_screenFlashFX;
	UIPauseMenuView* m_uiPauseMenuView;
};