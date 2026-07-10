#pragma once

#include "UIMenuView.h"

#include <string>

class Graphics;
class Input;
class UIImageView;
class UISpriteText;

class UIGameOverView : public UIMenuView
{
public:
	UIGameOverView();
	virtual ~UIGameOverView();
	
	void Init(std::string name, Input* input);
	void Render(Graphics* graphics) override;
	void Shutdown() override;
	virtual void OnCancelPressed() override {}

protected:
	virtual void TransitionIn(bool isAnimating) override;
	virtual void SetupNavigation() override;

private:
	static void Retry(UIMenuView* owner);
	static void Quit(UIMenuView* owner);

	UIImageView* m_backgroundImage;
	UIImageView* m_overlayImage;
	UISpriteText* m_gameOverTitle;
};