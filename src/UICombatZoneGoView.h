#pragma once

#include "UIView.h"

#include <string>

class Graphics;
class UIImageView;

class UICombatZoneGoView : public UIView
{
public:
	UICombatZoneGoView();
	~UICombatZoneGoView();

	void Init(std::string name) override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;

	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;
	void Shutdown() override;

private:
	static constexpr float DisplayDuration = 5.0f;
	static constexpr float FadeOutDuration = 0.3f;
	static constexpr float FlashFrequency = 10.0f;
	static constexpr float MaxPulseScale = 1.12f;

	UIImageView* m_goImage;
	float m_timer;
};
