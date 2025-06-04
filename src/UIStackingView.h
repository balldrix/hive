#pragma once

#include "Frame.h"
#include "UIMenuItemView.h"
#include "UIView.h"

#include <string>
#include <vector>

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

	std::vector<UIMenuItemView*> GetMenuItems() const { return m_childViews; }
	UIMenuItemView::SelectionStates GetSelectionState(int index) const;

	void SetOrientation(Orientations orientation);
	void SetSpacing(int spacing);

	void UpdateLayout(Frame frame);
	void AddView(UIMenuItemView* uiView);

protected:
	virtual void Shutdown();

	Orientations m_orientation;
	int m_spacing;
	std::vector<UIMenuItemView*> m_childViews;
};
