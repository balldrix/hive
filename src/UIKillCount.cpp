#include "UIKillCount.h"

#include "UIConfig.h"
#include "UISpriteText.h"

UIKillCount::UIKillCount() :
	m_labelText(nullptr),
	m_countText(nullptr)
{
}

UIKillCount::~UIKillCount()
{
	Shutdown();
}

void UIKillCount::Init(std::string name)
{
	m_name = name;

	m_labelText = new UISpriteText();
	m_labelText->Init(UIConfig::ThaleahFont12);
	m_labelText->SetColour(Color(0.85f, 0.65f, 0.65f));
	m_labelText->SetOutline(true, Color(0.65f, 0.145f, 0.145f));
	m_labelText->SetText("KO'S");
	m_labelText->SetPosition(Vector2(166.0f, 124.0f));
	m_labelText->SetAlignment(UISpriteText::Alignments::Right);
	m_labelText->SetActive(true);
}

void UIKillCount::Render(Graphics* graphics)
{
	m_labelText->Render(graphics);
}

void UIKillCount::Shutdown()
{
	delete m_labelText;
	m_labelText = nullptr;

	delete m_countText;
	m_countText = nullptr;
}

void UIKillCount::SetValue(int count)
{
}
