#pragma once

#include "UIView.h"

#include <string>

class Graphics;
class UISpriteText;

class UIKillCount : public UIView
{
public:
	UIKillCount();
	~UIKillCount();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;

	void SetValue(int count);
	void UpdateKills(int count);

private:
	UISpriteText* m_labelText;
	UISpriteText* m_countText;

	int m_currentCountWidth;
	int m_previousCount;
	int m_targetCount;
	float m_updateTimer;
};