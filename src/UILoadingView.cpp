#include "UILoadingView.h"

#include "AssetLoader.h"
#include "Graphics.h"

UILoadingView::UILoadingView()
{
}

UILoadingView::~UILoadingView()
{
	Shutdown();
}

void UILoadingView::Init()
{
	Logger::LogInfo("Initialising UI Loading View.");

	m_sprite = new Sprite();
	m_sprite->Init(AssetLoader::GetTexture("loadingScreen_bg"));
	m_sprite->SetOrigin(Vector2::Zero);
	m_isActive = true;
}

void UILoadingView::Render(Graphics* graphics)
{
	if(m_isActive)
		m_sprite->Render(graphics);
}

void UILoadingView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Loading View.");

	delete m_sprite;
	m_sprite = nullptr;
}