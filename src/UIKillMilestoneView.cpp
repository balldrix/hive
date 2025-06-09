#include "UIKillMilestoneView.h"

#include "UIConfig.h"
#include "GlobalConstants.h"
#include "UIManager.h"
#include "UISpriteText.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

using namespace GlobalConstants;

UIKillMilestoneView::UIKillMilestoneView() :
	m_spriteText(nullptr),
	m_timer(0)
{
}

UIKillMilestoneView::~UIKillMilestoneView()
{
	Shutdown();
}

void UIKillMilestoneView::Init(std::string name)
{
	m_name = name;
	m_spriteText = new UISpriteText();
	m_spriteText->Init(UIConfig::GameBoy28);
	m_spriteText->SetColour(Color(0.96f, 0.91f, 0.91f));
	m_spriteText->SetOutline(true, Color(0.65f, 0.145f, 0.145f));
	m_spriteText->SetPosition(Vector2(GameWidth * 0.5f, GameHeight * 0.5f));
	m_spriteText->SetDepth(1.0f);

	m_spriteText->SetActive(true);

	UIManager::RegisterUIView(this);
}

void UIKillMilestoneView::Update(float deltaTime)
{
	if(!m_isActive) return;

	m_timer -= deltaTime;

	if(m_timer <= 0.0f) TransitionOut(true);
}

void UIKillMilestoneView::Render(Graphics* graphics)
{
	if(!m_isActive || m_isForcedHidden) return;

	m_spriteText->Render(graphics);
}

void UIKillMilestoneView::TransitionIn(bool isAnimating)
{
	m_currentViewState = UIView::ViewStates::Visible;
	m_timer = 2.0f;
	m_isActive = true;
}

void UIKillMilestoneView::SetValue(int count)
{
	TransitionIn(true);
	m_spriteText->SetText(fmt::format("{}", count));
	m_spriteText->SetAlignment(UISpriteText::Alignments::Centre);
}

void UIKillMilestoneView::Shutdown()
{
	UIManager::UnregisterUIView(this);

	delete m_spriteText;
	m_spriteText = nullptr;
}