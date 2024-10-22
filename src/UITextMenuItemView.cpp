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
	m_currentSelectedState = SelectedStates::NotSelected;
}

void UITextMenuItemView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_uiSpriteText->Render(graphics);
}

void UITextMenuItemView::Shutdown()
{
	delete m_uiSpriteText;
	m_uiSpriteText = nullptr;
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
}

void UITextMenuItemView::SetPosition(const Vector2& position)
{
	m_uiSpriteText->SetPosition(position);
}

void UITextMenuItemView::SetColour(Color colour)
{
	m_uiSpriteText->SetColour(colour);
}
