#include "UIHudView.h"

#include "Logger.h"
#include "UIEnemyStatsView.h"
#include "UIManager.h"
#include "UIPlayerStatsView.h"
#include "UIView.h"

#include <string>

UIHudView::UIHudView() : 
	m_playerStatsView(nullptr),
	m_enemyStatsView(nullptr)
{
}

UIHudView::~UIHudView()
{
	Shutdown();
}

void UIHudView::Init(std::string name)
{
	m_name = name;

	Logger::LogInfo("Initialising UI Hud View");

	m_playerStatsView = new UIPlayerStatsView();
	m_playerStatsView->Init("Player Stats View");
	m_playerStatsView->TransitionOut(false);

	m_enemyStatsView = new UIEnemyStatsView();
	m_enemyStatsView->Init("Enemy Stats View");

	m_assignedStates.push_back("Gameplay");

	UIManager::RegisterUIView(this);

	m_isActive = true;
}

void UIHudView::Update(float deltaTime)
{
	m_playerStatsView->Update(deltaTime);
}

void UIHudView::Render(Graphics* graphics)
{
	m_playerStatsView->Render(graphics);
}

void UIHudView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Hud View");

	UIManager::UnregisterUIView(this);

	delete m_enemyStatsView;
	m_enemyStatsView = nullptr;

	delete m_playerStatsView;
	m_playerStatsView = nullptr;
}
