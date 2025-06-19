#pragma once

#include "Graphics.h"
#include "UIMenuItemView.h"
#include "UISpriteText.h"

#include <directxtk/SimpleMath.h>
#include <map>
#include <string>

using namespace DirectX;
using namespace SimpleMath;

class UITextMenuItemView : public UIMenuItemView
{
public:
	UITextMenuItemView();
	~UITextMenuItemView();

	void Init(std::string name) override;
	void Render(Graphics* graphics) override;
	void Shutdown() override;
	void ChangeSelectionState(SelectionStates selectedState) override;
	void HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState) override;

	void SetActive(bool isActive) override;

	int GetHeight() const override { return m_uiSpriteText->GetHeight(); }
	int GetWidth() const override { return m_uiSpriteText->GetWidth(); }
	Color GetColour() override { return m_uiSpriteText->GetColour(); }

	void SetText(std::string text);
	void SetSelectedStateColours(Color selected, Color unselected, Color disabled);
	void SetPosition(const Vector2& position);
	virtual void SetColour(Color colour);
	void SetAlignment(UISpriteText::Alignments alignment);

protected:
	virtual void SelectNextOption() {};
	virtual void SelectPreviousOption() {};
	virtual void HandleOptionChange(int index) {};


	Color m_selectedTextColour;
	Color m_unselectedTextColour;
	Color m_disabledTextColour;
	int m_selectedIndex;

private:
	UISpriteText* m_uiSpriteText;

	typedef std::map<UIMenuItemView::SelectionStates, Color> SelectedStateColours;
	SelectedStateColours m_selectionStateColours;
};