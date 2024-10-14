#include "UILoadingView.h"

#include "AssetLoader.h"
#include "UIImageView.h"
#include "Graphics.h"
#include "Sprite.h"
#include "UIManager.h"

UILoadingView::UILoadingView() :
	m_loadingBackground(nullptr)
{
}

UILoadingView::~UILoadingView()
{
	Shutdown();
}

void UILoadingView::Init(std::string name)
{
	m_name = name;

	Logger::LogInfo("Initialising UI Loading View.");

	m_loadingBackground = new UIImageView();
	m_loadingBackground->Init("Background Image");
	m_loadingBackground->GetSprite()->Init(AssetLoader::GetTexture("loadingScreen_bg"));
	m_loadingBackground->GetSprite()->SetOrigin(Vector2::Zero);

	m_assignedStates.push_back("Loading");

	UIManager::RegisterUIView(this);
}

void UILoadingView::Render(Graphics* graphics)
{
	if(m_isActive)
		m_loadingBackground->Render(graphics);
}

void UILoadingView::TransitionIn(bool isAnimating)
{
	m_currentViewState = UIView::ViewState::Visible;
	m_loadingBackground->SetActive(true);
	m_isActive = true;
}

void UILoadingView::TransitionOut(bool isAnimating)
{
	m_currentViewState = UIView::ViewState::NotVisible;
	m_loadingBackground->SetActive(false);
	m_isActive = false;
}

void UILoadingView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Loading View.");

	UIManager::UnregisterUIView(this);

	delete m_loadingBackground;
	m_loadingBackground = nullptr;
}