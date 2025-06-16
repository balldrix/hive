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

	void Init(std::string name, float min = 0.0f, float max = 1.0f, float defaultValue = 0.0f, Color colour = Colors::White.v);
	void SetPosition(const Vector2& position);

	void Render(Graphics* graphics) override;

private:
	UIBarView* m_sliderBar;
};