#include "UISystemView.h"

#include "Logger.h"
#include "UIFadeOverlayView.h"
#include "UILoadingView.h"
#include "UIView.h"

#include <string>

UISystemView::UISystemView() :
	m_fadeOverlayView(nullptr),
	m_loadingView(nullptr)
{
}

UISystemView::~UISystemView()
{
	Shutdown();
}

void UISystemView::Init(std::string name)
{
	m_name = name;

	Logger::LogInfo("Initialising UI System View.");

	m_fadeOverlayView = new UIFadeOverlayView();
	m_fadeOverlayView->Init("UI Fade Overlay View");
	m_fadeOverlayView->TransitionOut(false);

	m_loadingView = new UILoadingView();
	m_loadingView->Init("UI Loading View");
	m_loadingView->TransitionOut(false);

	m_isActive = true;
}

void UISystemView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	//m_loadingView->Render(graphics);
	m_fadeOverlayView->Render(graphics);
}

void UISystemView::Update(float deltaTime)
{
	if(!m_isActive) return;

	m_fadeOverlayView->Update(deltaTime);
}

void UISystemView::FadeOut()
{
	m_fadeOverlayView->TransitionIn(true);
}

void UISystemView::FadeIn()
{
	m_fadeOverlayView->TransitionOut(true);
}

bool UISystemView::IsFading()
{
	return m_fadeOverlayView->IsAnimating();
}

void UISystemView::Shutdown()
{
	Logger::LogInfo("Shutting down UI System View.");

	delete m_loadingView;
	m_loadingView = nullptr;

	delete m_fadeOverlayView;
	m_fadeOverlayView = nullptr;
}
