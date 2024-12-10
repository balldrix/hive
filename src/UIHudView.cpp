#include "UIHudView.h"

#include "Logger.h"
#include "UIManager.h"
#include "UIPlayerInfoView.h"
#include "UIView.h"

#include <string>

UIHudView::UIHudView() : 
	m_playerInfoView(nullptr)
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

	m_playerInfoView = new UIPlayerInfoView();
	m_playerInfoView->Init("UI Player Info View");
	m_playerInfoView->TransitionOut(false);

	m_assignedStates.push_back("Gameplay");

	UIManager::RegisterUIView(this);

	m_isActive = true;
}

void UIHudView::Render(Graphics* graphics)
{
	m_playerInfoView->Render(graphics);
}

void UIHudView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Hud View");

	delete m_playerInfoView;
	m_playerInfoView = nullptr;
}
