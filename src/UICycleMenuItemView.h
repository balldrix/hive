#pragma once

#include "UIImageView.h"
#include "UITextMenuItemView.h"

class UICycleMenuItemView : public UITextMenuItemView
{
public:
	UICycleMenuItemView();
	~UICycleMenuItemView();

	void Init(std::string name, std::vector<std::string> options, int defaultIndex, void (*delegate)(int));
	
	void SetPosition(const Vector2& position);
	void SetColour(Color colour) override;

	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

protected:
	void SelectNextOption() override;
	void SelectPreviousOption() override;
	void HandleOptionChange(int index) override;

private:
	int m_currentIndex;
	std::vector<std::string> m_options;
	void (*onOptionChanged)(int);
	float m_repeatTimer;

	UIImageView* m_leftArrow;
	UIImageView* m_rightArrow;
	UISpriteText* m_optionText;
};