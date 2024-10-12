#pragma once

#include "UIImageView.h"

class UILoadingView : public UIView
{
public:
	UILoadingView();
	~UILoadingView();

	void Init();
	void Render(Graphics* graphics);

	void TransitionIn(bool isAnimating);
	void TransitionOut(bool isAnimating);

	void Shutdown();

private:
	UIImageView* m_loadingBackground;
};