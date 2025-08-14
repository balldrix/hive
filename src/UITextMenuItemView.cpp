#include "UITextMenuItemView.h"

#include "Graphics.h"
#include "Input.h"
#include "UIConfig.h"
#include "UIMenuItemView.h"
#include "UISpriteText.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

UITextMenuItemView::UITextMenuItemView() :
	m_uiSpriteText(nullptr)
{
}

UITextMenuItemView::~UITextMenuItemView()
{
	Shutdown();
}

void UITextMenuItemView::Init(std::string name, Input* input)
{
	m_name = name;
	m_input = input;

	m_uiSpriteText = new UISpriteText();
	m_uiSpriteText->Init(UIConfig::DespairFont8);
	m_uiSpriteText->SetAlignment(UISpriteText::Alignments::Left);
	m_uiSpriteText->SetActive(false);
	m_uiSpriteText->SetColour(m_unselectedTextColour);
	m_uiSpriteText->SetDepth(0.5f);
	m_selectionState = SelectionStates::UnSelected;
	m_isActive = false;
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

void UITextMenuItemView::HandleSelectionStateChanged(SelectionStates previousSelectionState, SelectionStates newSelectionState)
{
	auto it = m_selectionStateColours.find(newSelectionState);
	if(it != m_selectionStateColours.end())
	{
		m_uiSpriteText->SetColour(it->second);
	}
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

void UITextMenuItemView::SetPosition(const Vector2& position)
{
	m_uiSpriteText->SetPosition(position);
}

void UITextMenuItemView::SetColour(Color colour)
{
	m_uiSpriteText->SetColour(colour);
}

void UITextMenuItemView::SetAlpha(float alpha)
{
	Color colour = m_uiSpriteText->GetColour();
	colour.A(alpha);
	m_uiSpriteText->SetColour(colour);
}

void UITextMenuItemView::SetDepth(float depth)
{
	m_uiSpriteText->SetDepth(depth);
}

void UITextMenuItemView::SetAlignment(UISpriteText::Alignments alignment)
{
	m_uiSpriteText->SetAlignment(alignment);
}
