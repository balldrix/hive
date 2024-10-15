#pragma once

#include "UIImageView.h"

class UILoadingView : public UIView
{
public:
	UILoadingView();
	~UILoadingView();

	void Init(std::string name);
	void Render(Graphics* graphics);

	void Update(float deltaTime);
	void TransitionIn(bool isAnimating);
	void TransitionOut(bool isAnimating);

	void Shutdown();

private:
	UIImageView* m_loadingBackground;
};