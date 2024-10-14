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

	void Init(std::string name);
	void Render(Graphics* graphics);
	void Update(float deltaTime);
		
	void FadeOut();
	void FadeIn();

	std::string GetName() const { return m_name; }

	bool IsFading();

	virtual void Shutdown();

private:
	UIFadeOverlayView* m_fadeOverlayView;
	UILoadingView* m_loadingView;
};