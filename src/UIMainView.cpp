#include "UIMainView.h"

#include "Logger.h"
#include "UIHudView.h"
#include "UIManager.h"
#include "UIView.h"

#include <string>

UIMainView::UIMainView() :
	m_uiHudView(nullptr)
{
}

UIMainView::~UIMainView()
{
	Shutdown();
}

void UIMainView::Init(std::string name)
{
	Logger::LogInfo("Initialising UI Main View");

	m_name = name;

	m_uiHudView = new UIHudView();
	m_uiHudView->Init("UI Hud View");
	m_uiHudView->TransitionOut(false);
}

void UIMainView::Render(Graphics* graphics)
{
}

void UIMainView::FadeOut()
{
}

void UIMainView::FadeIn()
{
}

void UIMainView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Main View");

	UIManager::UnregisterUIView(this);

	delete m_uiHudView;
	m_uiHudView = nullptr;
}
