#include "UIComboCounterView.h"

#include "UIConfig.h"
#include "UIManager.h"
#include "UISpriteText.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

UIComboCounterView::UIComboCounterView() : 
	m_comboText(nullptr)
{
}

UIComboCounterView::~UIComboCounterView()
{
	Shutdown();
}

void UIComboCounterView::Init(std::string name)
{
	m_name = name;

	m_comboText = new UISpriteText();
	m_comboText->Init(UIConfig::GamerFont16);
	m_comboText->SetColour(Color(0.914f, 0.678f, 0.11f));
	m_comboText->SetText("0 COMBO'S");
	m_comboText->SetPosition(Vector2(3.0f, 33.0f));
	m_comboText->SetAlignment(UISpriteText::Alignments::Left);

	UIManager::RegisterUIView(this);
}

void UIComboCounterView::Render(Graphics* graphics)
{
	m_comboText->Render(graphics);
}

void UIComboCounterView::Shutdown()
{
	UIManager::UnregisterUIView(this);

	delete m_comboText;
	m_comboText = nullptr;
}

void UIComboCounterView::SetCombo(const int& value)
{
	m_comboText->SetActive(true);
	m_comboText->SetText(fmt::format("{} COMBO!", value));
}

void UIComboCounterView::TransitionOut(bool IsAnimated)
{
	m_comboText->SetActive(false);
}
