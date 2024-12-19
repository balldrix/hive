#pragma once

#include "UIView.h"
#include <string>

class UISpriteText;
class Graphics;

class UIKillMilestoneView : public UIView
{
public:
	UIKillMilestoneView();
	~UIKillMilestoneView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	void TransitionIn(bool isAnimating) override;

	void SetValue(int count);

	void Shutdown() override;

private:
	UISpriteText* m_spriteText;
	float m_timer;
};