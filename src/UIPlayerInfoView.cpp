#include "UIPlayerInfoView.h"

#include "Logger.h"
#include "UIProfileView.h"
#include "UIView.h"

#include <string>

UIPlayerInfoView::UIPlayerInfoView() :
	m_profileView(nullptr)
{
}

UIPlayerInfoView::~UIPlayerInfoView()
{
	Shutdown();
}

void UIPlayerInfoView::Init(std::string name)
{
	m_name = name;

	m_profileView = new UIProfileView();
	m_profileView->Init("Player Profile View");
}

void UIPlayerInfoView::Update(float deltaTime)
{
}

void UIPlayerInfoView::Render(Graphics* graphics)
{
	m_profileView->Render(graphics);
}

void UIPlayerInfoView::TransitionIn(bool isAnimating)
{
}

void UIPlayerInfoView::TransitionOut(bool isAnimating)
{
}

void UIPlayerInfoView::Shutdown()
{
	Logger::LogInfo("Shutting down UI PlayerInfoView");

	delete m_profileView;
	m_profileView = nullptr;
}

void UIPlayerInfoView::DoTransition(float deltaTime)
{
}
