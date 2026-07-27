#pragma once

#include "UIMenuView.h"

#include <string>

class Graphics;
class Input;
class UIImageView;
class UISpriteText;

class UIDemoEndView : public UIMenuView
{
public:
	UIDemoEndView();
	virtual ~UIDemoEndView();

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
	static void Wishlist(UIMenuView* owner);

	UIImageView* m_backgroundImage;
	UIImageView* m_overlayImage;
	UISpriteText* m_demoEndTitle;
};