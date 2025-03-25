#pragma once

#include "Graphics.h"
#include "UIImageView.h"
#include "UIView.h"

#include <string>

class UILoadingView : public UIView
{
public:
	UILoadingView();
	~UILoadingView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;

	void Update(float deltaTime) override;
	void TransitionIn(bool isAnimating) override;
	void TransitionOut(bool isAnimating) override;

	void Shutdown();

private:
	UIImageView* m_loadingBackground;
};