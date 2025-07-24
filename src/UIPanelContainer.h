#pragma once

#include "UIView.h"

#include <string>
#include <Windows.h>

class UIImageView;
class Graphics;

class UIPanelContainer : public UIView
{
public:
	UIPanelContainer();
	~UIPanelContainer();

	void Init(const std::string& name, const RECT& rect);
	void Render(Graphics* graphics) override;

	void Shutdown() override;

	void SetActive(bool isActive) override;
	void SetOverlayAlpha(float alpha);
	void SetPanelAlpha(float alpha);

private:
	UIImageView* m_overlayImage;
	UIImageView* m_panelImage;
};