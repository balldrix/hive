#pragma once

#include "UIImageView.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>

class Graphics;

static const float FadeDuration = 0.4f;
static const Color OpaqueColour = Colors::Black.v;

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