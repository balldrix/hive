#pragma once

#include "UIView.h"

class UISpriteText;
class UIImageView;

class UITitleScreenView : public UIView
{
public:
	UITitleScreenView();
	virtual ~UITitleScreenView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void Update(float deltaTime) override;

	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;

	void Shutdown() override;
private:
	UISpriteText* m_startGameText;
	UIImageView* m_logoImage;
};