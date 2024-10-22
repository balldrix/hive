#pragma once

#include "UIView.h"
#include "Frame.h"

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

	void SetHeight(int height);
	void SetWidth(int width);
	void SetOrientation(Orientations orientation);
	void SetSpacing(int spacing);

	void UpdateLayout(Frame frame);

	void AddView(UIView* uiView);

	std::vector<UIView*> GetViews() const { return m_childViews; }

protected:
	virtual void Shutdown();

	Orientations m_orientation;
	int m_spacing;
	int m_stackedViewsHeight;
	int m_stackedViewsWidth;
	std::vector<UIView*> m_childViews;
};
