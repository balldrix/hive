#include "UIEnemyStatsView.h"

#include "UIBarView.h"
#include "UIManager.h"
#include "UIPortraitView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

UIEnemyStatsView::UIEnemyStatsView() :
	m_portraitView(nullptr),
	m_healthBar(nullptr)
{
}

UIEnemyStatsView::~UIEnemyStatsView()
{
	Shutdown();
}

void UIEnemyStatsView::Init(std::string name)
{
	m_name = name;

	m_portraitView = new UIPortraitView();
	m_portraitView->Init("Enemy Portrait");
	m_portraitView->SetPosition(Vector2(2.0f, 2.0f));

	UIManager::RegisterUIView(m_portraitView);
}

void UIEnemyStatsView::Render(Graphics* graphics)
{
	m_portraitView->Render(graphics);
}

void UIEnemyStatsView::Shutdown()
{
	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_portraitView;
	m_portraitView = nullptr;
}
