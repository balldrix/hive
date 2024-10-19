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
	m_loadingBackground->GetSprite()->Init(AssetLoader::GetTexture("t_loadingScreen_bg"));
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
	case UIView::ViewStates::NotVisible:
		break;
	case UIView::ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
		break;
	case UIView::ViewStates::Visible:
		break;
	case UIView::ViewStates::AnimatingOut:
		m_currentViewState = ViewStates::NotVisible;
		m_loadingBackground->SetActive(false);
		m_isActive = false;
		break;
	default:
		break;
	}
}

void UILoadingView::TransitionIn(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition In: UI Loading View {} animation.", isAnimating ? "with" : "without"));

	m_loadingBackground->TransitionIn(isAnimating);
	m_loadingBackground->SetActive(true);
	m_isActive = true;

	if(isAnimating)
	{
		m_currentViewState = UIView::ViewStates::AnimatingIn;
		return;
	}

	m_currentViewState = UIView::ViewStates::Visible;
}

void UILoadingView::TransitionOut(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition Out: UI Loading View {} animation.", isAnimating ? "with" : "without"));

	if(isAnimating)
	{
		m_currentViewState = UIView::ViewStates::AnimatingOut;
		return;
	}

	m_currentViewState = UIView::ViewStates::NotVisible;
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