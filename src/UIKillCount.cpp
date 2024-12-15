#include "UIKillCount.h"

#include "UIConfig.h"
#include "UISpriteText.h"

#include <fmt/format.h>

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
	m_labelText->SetColour(Color(0.96f, 0.91f, 0.91f));
	m_labelText->SetOutline(true, Color(0.65f, 0.145f, 0.145f));
	m_labelText->SetText("KO'S");
	m_labelText->SetPosition(Vector2(162.0f, 128.0f));
	m_labelText->SetAlignment(UISpriteText::Alignments::Right);
	m_labelText->SetActive(true);

	m_countText = new UISpriteText();
	m_countText->Init(UIConfig::GamerFont34);
	m_countText->SetColour(Color(0.96f, 0.91f, 0.91f));
	m_countText->SetOutline(true, Color(0.65f, 0.145f, 0.145f));
	m_countText->SetText(fmt::format("{:06}", 0));
	m_countText->SetPosition(Vector2(236.0f, 125.0f));
	m_countText->SetAlignment(UISpriteText::Alignments::Right);
	m_countText->SetActive(true);
}

void UIKillCount::Render(Graphics* graphics)
{
	m_labelText->Render(graphics);
	m_countText->Render(graphics);
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
	m_countText->SetText(fmt::format("{:06}", count));
}
