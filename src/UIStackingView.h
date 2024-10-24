#pragma once

#include "UIView.h"
#include "Frame.h"

class UIMenuItemView;

class UIStackingView : public UIView
{
public:
	enum Orientations
	{
		Horizontal,
		Vertical
	};

	UIStackingView();
	virtual ~UIStackingView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void SetActive(bool isActive) override;

	void SetOrientation(Orientations orientation);
	void SetSpacing(int spacing);

	void UpdateLayout(Frame frame);

	void AddView(UIMenuItemView* uiView);

	std::vector<UIMenuItemView*> GetMenuItems() const { return m_childViews; }

protected:
	virtual void Shutdown();

	Orientations m_orientation;
	int m_spacing;
	std::vector<UIMenuItemView*> m_childViews;
};
