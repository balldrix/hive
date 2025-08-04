#pragma once

#include "UIMenuItemView.h"
#include "UITextMenuItemView.h"

#include <directxtk/SimpleMath.h>
#include <string>
#include <vector>

class Graphics;
class Input;
class UITextMenuItemView;
class UIImageView;
class UIMenuView;
class UISpriteText;

class UICycleMenuItemView : public UIMenuItemView
{
public:
	UICycleMenuItemView();
	~UICycleMenuItemView();

	void Init(std::string name, Input* input, std::vector<std::string> options, int defaultIndex, void (*delegate)(UIMenuView* owner, int), UIMenuView* owner);
	
	int GetHeight() const override { return m_labelText->GetHeight(); }
	int GetWidth() const override;

	void SetActive(bool isActive) override;
	void SetPosition(const Vector2& position);
	void SetColour(Color colour) override;
	void SetAlpha(float alpha) override;

	void Render(Graphics* graphics) override;
	void Shutdown() override;

protected:
	void HandleOptionChange(int index) override;
	void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) override;

private:
	int m_currentIndex;
	std::vector<std::string> m_options;
	void (*onOptionChanged)(UIMenuView* owner, int);
	float m_repeatTimer;

	UITextMenuItemView* m_labelText;
	UIImageView* m_leftArrow;
	UIImageView* m_rightArrow;
	UISpriteText* m_optionText;
};