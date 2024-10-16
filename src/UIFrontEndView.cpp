#include "UIFrontEndView.h"

#include "UIImageView.h"
#include "UIManager.h"
#include "Sprite.h"
#include "AssetLoader.h"
#include "Logger.h"

UIFrontEndView::UIFrontEndView() :
	m_background(nullptr)
{
}

UIFrontEndView::~UIFrontEndView()
{
	Shutdown();
}

void UIFrontEndView::Init(std::string name)
{
	m_name = name;

	Logger::LogInfo("Initialising UI Front End View.");

	m_background = new UIImageView();
	m_background->Init("UI Image View");
	m_background->TransitionOut(false);

	auto sprite = m_background->GetSprite();
	sprite->Init(AssetLoader::GetTexture("titleScreen_bg"));
	sprite->SetOrigin(Vector2::Zero);
	sprite->SetDepth(0.0f);

	AssignState("TitleScreen");
	UIManager::RegisterUIView(this);
	m_isActive = false;
}

void UIFrontEndView::Update(float deltaTime)
{
	if(m_isActive == false) return;

	switch (m_currentViewState)
	{
	case UIView::ViewState::NotVisible:
		break;
	case UIView::ViewState::AnimatingIn:
		m_currentViewState = ViewState::Visible;
		m_background->SetActive(true);
		break;
	case UIView::ViewState::Visible:
		break;
	case UIView::ViewState::AnimatingOut:
		m_currentViewState = ViewState::NotVisible;
		m_background->SetActive(false);
		m_isActive = false;
		break;
	default:
		break;
	}
}

void UIFrontEndView::Render(Graphics* graphics)
{
	if(m_isActive == false) return;
	m_background->Render(graphics);
}

void UIFrontEndView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Front End View.");
	
	UIManager::UnregisterUIView(this);

	delete m_background;
	m_background = nullptr;
}

void UIFrontEndView::TransitionIn(bool isAnimating)
{
	m_currentViewState = UIView::ViewState::AnimatingIn;
	m_isActive = true;
}

void UIFrontEndView::TransitionOut(bool isAnimating)
{
	m_currentViewState = UIView::ViewState::AnimatingOut;
}
