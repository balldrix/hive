#pragma once

#include "UIImageView.h"

class UILoadingView : UIImageView
{
public:
	UILoadingView();
	~UILoadingView();

	void Init();
	void Render(Graphics* graphics);
	void Shutdown();
};