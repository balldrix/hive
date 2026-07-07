#pragma once

#include "UIMenuView.h"

#include <string>

class Graphics;
class Input;
class UIImageView;

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

private:
	static void Retry(UIMenuView* owner);
	static void Quit(UIMenuView* owner);
	static void Wishlist(UIMenuView* owner);

	UIImageView* m_backgroundImage;
};