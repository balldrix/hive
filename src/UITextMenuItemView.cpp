#include "UITextMenuItemView.h"

#include "UISpriteText.h"
#include "UIConfig.h"

UITextMenuItemView::UITextMenuItemView() :
	m_uiSpriteText(nullptr)
{
}

UITextMenuItemView::~UITextMenuItemView()
{
	Shutdown();
}

void UITextMenuItemView::Init(std::string name)
{
	m_name = name;
	m_uiSpriteText = new UISpriteText();
	m_uiSpriteText->Init(UIConfig::DespairFont8);
	m_uiSpriteText->SetAlignment(UISpriteText::Alignments::Left);
	m_uiSpriteText->SetActive(false);
	m_uiSpriteText->SetColour(m_unselectedTextColour);
	m_selectionState = SelectionStates::UnSelected;
	m_isActive = false;
}

void UITextMenuItemView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	auto it = m_selectionStateColours.find(m_selectionState);

	if(it != m_selectionStateColours.end() && m_uiSpriteText->GetColour() != m_selectionStateColours[m_selectionState])
	{
		m_uiSpriteText->SetColour(m_selectionStateColours[m_selectionState]);
	}

	m_uiSpriteText->Render(graphics);
}

void UITextMenuItemView::Shutdown()
{
	delete m_uiSpriteText;
	m_uiSpriteText = nullptr;
}

void UITextMenuItemView::ChangeSelectionState(SelectionStates selectionState)
{
	SelectionStates previous = m_selectionState;
	m_selectionState = selectionState;
	HandleSelectionStateChanged(previous, selectionState);
}

void UITextMenuItemView::HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState)
{
}

void UITextMenuItemView::SetActive(bool isActive)
{
	m_isActive = isActive;
	m_uiSpriteText->SetActive(isActive);
}

void UITextMenuItemView::SetText(std::string text)
{
	m_uiSpriteText->SetText(text);
}

void UITextMenuItemView::SetSelectedStateColours(Color selected, Color unselected, Color disabled)
{
	m_selectedTextColour = selected;
	m_unselectedTextColour = unselected;
	m_disabledTextColour = disabled;

	m_selectionStateColours =
	{
		{ UIMenuItemView::SelectionStates::Selected, m_selectedTextColour },
		{ UIMenuItemView::SelectionStates::UnSelected, m_unselectedTextColour },
		{ UIMenuItemView::SelectionStates::Disabled, m_disabledTextColour }
	};
}

void UITextMenuItemView::SetPosition(const Vector2& position)
{
	m_uiSpriteText->SetPosition(position);
}

void UITextMenuItemView::SetColour(Color colour)
{
	m_uiSpriteText->SetColour(colour);
}
