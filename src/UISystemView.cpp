#include "UISystemView.h"

UISystemView::UISystemView() :
	m_fadeOverlayView(nullptr)
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
	m_isActive = true;
}

void UISystemView::Render(Graphics* graphics)
{
	if(m_isActive)
		m_fadeOverlayView->Render(graphics);
}

void UISystemView::Update(float deltaTime)
{
	if(m_isActive)
		m_fadeOverlayView->Update(deltaTime);
}

void UISystemView::Shutdown()
{
	Logger::LogInfo("Shutting down UI System View.");

	delete m_fadeOverlayView;
	m_fadeOverlayView = nullptr;
}
