#pragma once
#pragma once

#include "UIView.h"

class UIImageView;
class UITitleScreenView;
class UIMainMenuView;
class UIOptionsView;

class UIFrontEndView : UIView
{
public:
	UIFrontEndView();
	virtual ~UIFrontEndView();

	void Init(std::string name);
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	void Shutdown() override;

	void TransitionIn(bool isAnimating);
	void TransitionOut(bool isAnimating);

private:
	UIImageView* m_background;
	UITitleScreenView* m_titleScreenView;
	UIMainMenuView* m_mainMenuView;
	UIOptionsView* m_optionsView;
};