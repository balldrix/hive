#pragma once

#include "UIView.h"

class UISpriteText;

class UITitleScreenView : public UIView
{
public:
	UITitleScreenView();
	virtual ~UITitleScreenView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;
private:
	UISpriteText* m_startGameText;
};