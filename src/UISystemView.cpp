#include "UISystemView.h"

#include "Graphics.h"
#include "Logger.h"
#include "UIFadeOverlayView.h"
#include "UILoadingView.h"
#include "UIOptionsView.h"
#include "UIView.h"

#include <string>

UISystemView::UISystemView() :
	m_fadeOverlayView(nullptr),
	m_loadingView(nullptr),
	m_optionsView(nullptr)
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

	m_optionsView = new UIOptionsView();
	m_optionsView->Init("Menu Options");
	m_optionsView->TransitionOut(false);

	m_isActive = true;
}

void UISystemView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

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

	delete m_optionsView;
	m_optionsView = nullptr;

	delete m_loadingView;
	m_loadingView = nullptr;

	delete m_fadeOverlayView;
	m_fadeOverlayView = nullptr;
}
