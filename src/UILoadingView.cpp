#include "UILoadingView.h"

#include "AssetLoader.h"
#include "UIImageView.h"
#include "Graphics.h"
#include "Sprite.h"

UILoadingView::UILoadingView() :
	m_loadingBackground(nullptr)
{
}

UILoadingView::~UILoadingView()
{
	Shutdown();
}

void UILoadingView::Init()
{
	Logger::LogInfo("Initialising UI Loading View.");

	m_loadingBackground = new UIImageView();
	m_loadingBackground->Init();
	m_loadingBackground->GetSprite()->Init(AssetLoader::GetTexture("loadingScreen_bg"));
}

void UILoadingView::Render(Graphics* graphics)
{
	if(m_isActive)
		m_loadingBackground->Render(graphics);
}

void UILoadingView::TransitionIn(bool isAnimating)
{
	m_loadingBackground->TransitionIn(isAnimating);
}

void UILoadingView::TransitionOut(bool isAnimating)
{
	m_loadingBackground->TransitionOut(isAnimating);
}

void UILoadingView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Loading View.");

	delete m_loadingBackground;
	m_loadingBackground = nullptr;
}