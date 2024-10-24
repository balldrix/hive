#pragma once

#include "UIView.h"

class UIMenuItemView : public UIView
{
public:

	enum class SelectedStates
	{
		NotSelected,
		Selected,
		Disabled
	};

	UIMenuItemView();
	virtual ~UIMenuItemView() {};
	virtual void OnConfirmPressed() {};
	virtual void OnChangeSelection(SelectedStates selectedState) {};
	virtual void OnSelect() {};
protected:
	SelectedStates m_currentSelectedState;
};