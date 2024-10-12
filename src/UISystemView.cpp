#include "UISystemView.h"

#include "UIFadeOverlayView.h"
#include "UILoadingView.h"
#include "Logger.h"

UISystemView::UISystemView() :
	m_fadeOverlayView(nullptr),
	m_loadingView(nullptr)
{
}

UISystemView::~UISystemView()
{
	Shutdown();
}

void UISystemView::Init()
{
	Logger::LogInfo("Initialising UI System View.");

	m_fadeOverlayView = new UIFadeOverlayView();
	m_fadeOverlayView->Init();
	m_fadeOverlayView->TransitionOut(false);

	m_loadingView = new UILoadingView();
	m_loadingView->Init();
	m_loadingView->TransitionOut(false);

	m_isActive = true;
}

void UISystemView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_loadingView->Render(graphics);
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
