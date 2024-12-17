#pragma once

#include "UIView.h"

#include <string>

class UISpriteText;

class UIComboCounterView : public UIView
{
public:
	UIComboCounterView();
	~UIComboCounterView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void SetCombo(const int& value);

	void TransitionOut(bool IsAnimated) override;

private:
	UISpriteText* m_comboText;
};

