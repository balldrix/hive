#pragma once

#include "Graphics.h"
#include "UIBarView.h"
#include "UIMenuItemView.h"
#include "UITextMenuItemView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>

static const float SliderScaler = 10.0f;

class Input;
class UITextMenuItemView;
class UIBarView;
class UIMenuView;

class UISliderMenuItemView : public UIMenuItemView
{
public:
	UISliderMenuItemView();
	~UISliderMenuItemView();

	void Init(std::string name, Input* input, float max = 1.0f, int defaultValue = 0.0f, Color colour = Colors::White.v, void (*delegate)(UIMenuView* owner, int) = nullptr, UIMenuView* owner = nullptr);
	void Update(float deltaTime) override;

	int GetHeight() const override { return m_labelText->GetHeight(); }
	int GetWidth() const override { return m_labelText->GetWidth() + m_sliderBar->GetWidth(); }

	void SetActive(bool isActive) override;
	virtual void SetPosition(const Vector2& position);
	void SetColour(Color colour) override;
	void SetAlpha(float alpha) override;

	void Render(Graphics* graphics) override;
	void Shutdown() override;

protected:
	void HandleOptionChange(int index) override;
	void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) override;

private:
	void (*onSliderChanged)(UIMenuView* owner, int) = nullptr;
	UITextMenuItemView* m_labelText;
	UIBarView* m_sliderBar;
	float m_maxValue;
};