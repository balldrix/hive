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
	virtual ~UIMenuItemView();

	virtual void OnChangeSelection(SelectedStates selectedState) {};
	void AddOnSelectedListener(void(*onSelected)());
	void OnSelect();
protected:
	SelectedStates m_currentSelectedState;

private:
	void (*onSelected)();
};