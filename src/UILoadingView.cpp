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
	m_loadingBackground->GetSprite()->SetDepth(0.0f);

	m_assignedStates.push_back("Loading");

	UIManager::RegisterUIView(this);
}

void UILoadingView::Render(Graphics* graphics)
{
	if(m_isActive)
		m_loadingBackground->Render(graphics);
}

void UILoadingView::Update(float deltaTime)
{
	switch (m_currentViewState)
	{
	case UIView::ViewState::NotVisible:
		m_isActive = false;
		m_loadingBackground->SetActive(false);
		break;
	case UIView::ViewState::AnimatingIn:
		m_currentViewState = ViewState::Visible;
		break;
	case UIView::ViewState::Visible:
		break;
	case UIView::ViewState::AnimatingOut:
		m_currentViewState = ViewState::NotVisible;
		break;
	default:
		break;
	}
}

void UILoadingView::TransitionIn(bool isAnimating)
{
	m_isActive = true;
	m_loadingBackground->SetActive(true);

	if(isAnimating)
	{
		m_currentViewState = UIView::ViewState::AnimatingIn;
	}

	m_currentViewState = UIView::ViewState::Visible;
}

void UILoadingView::TransitionOut(bool isAnimating)
{
	if (isAnimating)
	{
		m_currentViewState = UIView::ViewState::AnimatingOut;
		return;
	}

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