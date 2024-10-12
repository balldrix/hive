#pragma once

#include "UIView.h"

class Graphics;
class UIFadeOverlayView;
class UILoadingView;

class UISystemView : UIView
{
public:
	UISystemView();
	virtual ~UISystemView();

	void Init();
	void Render(Graphics* graphics);
	void Update(float deltaTime);
		
	void FadeOut();
	void FadeIn();

	bool IsFading();

	virtual void Shutdown();

private:
	UIFadeOverlayView* m_fadeOverlayView;
	UILoadingView* m_loadingView;
};