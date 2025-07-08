#pragma once

#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <map>

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
	virtual void Update(float deltaTime);
	virtual void OnConfirmPressed() {};
	virtual void ChangeSelectionState(SelectionStates selectedState);
	virtual void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) {}
	virtual void OnSelect() {};
	virtual void SetSelectedStateColours(Color selected, Color unselected, Color disabled);
	virtual void SetPosition(const Vector2& position) {};
	virtual void SetColour(Color colour) {};
	virtual void SetAlpha(float alpha) {};
	
	void SetNavigation(Navigation navigation);

	SelectionStates GetSelectionState() const { return m_selectionState; }
	Navigation GetNavigation() const { return m_navigation; }

protected:
	virtual void SelectNextOption();
	virtual void SelectPreviousOption();
	virtual void HandleOptionChange(int index) {};

	Color m_selectedTextColour;
	Color m_unselectedTextColour;
	Color m_disabledTextColour;
	int m_selectedIndex;

	SelectionStates m_selectionState;
	Navigation m_navigation;

	typedef std::map<UIMenuItemView::SelectionStates, Color> SelectedStateColours;
	SelectedStateColours m_selectionStateColours;

private:
	float m_holdTimer;
	float m_repeatTimer;
	bool m_buttonPressed;
};