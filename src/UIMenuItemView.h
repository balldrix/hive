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

	struct Navigation
	{
		int up = -1;
		int down = -1;
		int left = -1;
		int right = -1;
	};

	UIMenuItemView();
	virtual ~UIMenuItemView() {};
	virtual void OnConfirmPressed() {};
	virtual void ChangeSelectionState(SelectionStates selectedState) {};
	virtual void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) {}
	virtual void OnSelect() {};
	
	SelectionStates GetSelectionState() const { return m_selectionState; }
	Navigation GetNavigation() const { return m_navigation; }

	void SetNavigation(Navigation navigation);

protected:
	SelectionStates m_selectionState;
	Navigation m_navigation;
};