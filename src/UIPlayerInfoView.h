#pragma once

#include "UIView.h"
#include <string>

class Graphics;
class UIBarView;
class UIPortraitView;

class UIPlayerInfoView : public UIView
{
public:
	UIPlayerInfoView();
	~UIPlayerInfoView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;

	void Shutdown() override;
private:
	void DoTransition(float deltaTime);

	UIPortraitView* m_portraitView;
	UIBarView* m_healthBar;
};