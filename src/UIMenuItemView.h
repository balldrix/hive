#pragma once

#include "UIView.h"

class UIMenuItemView : public UIView
{
public:

	enum class SelectionStates
	{
		UnSelected,
		Selected,
		Disabled
	};

	UIMenuItemView();
	virtual ~UIMenuItemView() {};
	virtual void OnConfirmPressed() {};
	virtual void ChangeSelectionState(SelectionStates selectedState) {};
	virtual void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) {}
	virtual void OnSelect() {};
protected:
	SelectionStates m_selectionState;
};