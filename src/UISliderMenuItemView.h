#pragma once

#include "Graphics.h"
#include "UIBarView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>

class UISliderMenuItemView : public UITextMenuItemView
{
public:
	UISliderMenuItemView();
	~UISliderMenuItemView();

	void Init(std::string name, float max = 1.0f, float defaultValue = 0.0f, Color colour = Colors::White.v);
	void SetPosition(const Vector2& position);

	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void (*onSliderChanged)(int) = nullptr;

protected:
	void SelectNextOption() override;
	void SelectPreviousOption() override;
	void HandleOptionChange(int index) override;

private:
	UIBarView* m_sliderBar;
	float m_holdTimer;
	bool m_buttonPressed;
	float m_maxValue;
};