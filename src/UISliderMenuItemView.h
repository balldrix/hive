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

	void Init(std::string name, float max = 1.0f, float defaultValue = 0.0f, Color colour = Colors::White.v, void (*delegate)(float) = nullptr);
	void SetPosition(const Vector2& position);
	void SetColour(Color colour) override;

	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void (*onSliderChanged)(float) = nullptr;

protected:
	void SelectNextOption() override;
	void SelectPreviousOption() override;
	void HandleOptionChange(int index) override;

private:
	UIBarView* m_sliderBar;
	float m_holdTimer;
	float m_repeatTimer;
	bool m_buttonPressed;
	float m_maxValue;
};