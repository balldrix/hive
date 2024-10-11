#pragma once

#include "UIFadeOverlayView.h"

class Graphics;

class UISystemView : UIView
{
public:
	UISystemView();
	virtual ~UISystemView();

	void Init();
	void Render(Graphics* graphics);
	void Update(float deltaTime);

	virtual void Shutdown();

private:
	UIFadeOverlayView* m_fadeOverlayView;
};