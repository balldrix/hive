#pragma once

#include "UIImageView.h"
#include "pch.h"

static const float FADE_DURATION = 0.4f;
static const Color OPAQUE_COLOR = Colors::Black.v;

class UIFadeOverlayView : public UIImageView
{
public:
	UIFadeOverlayView();
	virtual ~UIFadeOverlayView();

	void Init(std::string name) override;
	void Update(float deltaTime);
	void Render(Graphics* graphics) override;

	void TransitionIn(bool isAnimating);
	void TransitionOut(bool isAnimating);

	virtual void Shutdown();
private:
	float m_startingAlpha;
	float m_targetAlpha;
};