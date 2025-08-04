#pragma once

#include "UIView.h"

#include <string>

class Graphics;
class Input;
class UIFadeOverlayView;
class UILoadingView;
class UIOptionsView;
class Window;

class UISystemView : UIView
{
public:
	UISystemView();
	virtual ~UISystemView();

	void Init(std::string name, Window* window, Graphics* graphics, Input* input);
	void Update(float deltaTime);
	void Render(Graphics* graphics) override;
		
	void FadeOut();
	void FadeIn();

	std::string GetName() const { return m_name; }

	bool IsFading();

	virtual void Shutdown();

private:
	UIFadeOverlayView* m_fadeOverlayView;
	UILoadingView* m_loadingView;
	UIOptionsView* m_optionsView;
};