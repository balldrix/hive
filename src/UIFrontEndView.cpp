#include "UIFrontEndView.h"

#include "AssetLoader.h"
#include "Logger.h"
#include "Sprite.h"
#include "UIImageView.h"
#include "UIMainMenuView.h"
#include "UIManager.h"
#include "UITitleScreenView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

UIFrontEndView::UIFrontEndView() :
	m_background(nullptr),
	m_titleScreenView(nullptr),
	m_mainMenuView(nullptr)
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
	sprite->Init(AssetLoader::GetTexture("t_titleScreen_bg"));
	sprite->SetOrigin(Vector2::Zero);
	sprite->SetDepth(0.0f);

	UIManager::RegisterUIView(this);

	m_titleScreenView = new UITitleScreenView();
	m_titleScreenView->Init("Title Screen View");
	m_titleScreenView->TransitionOut(false);
	m_titleScreenView->AssignState("TitleScreen");

	m_mainMenuView = new UIMainMenuView();
	m_mainMenuView->Init("Main Menu View");
	m_mainMenuView->TransitionOut(false);
	m_mainMenuView->AssignState("MainMenu");

	AssignState("TitleScreen");
	AssignState("MainMenu");
	AssignState("FrontEndOptions");

	m_isActive = false;
}

void UIFrontEndView::Update(float deltaTime)
{
	if(m_isActive == false) return;

	switch (m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		break;
	case UIView::ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
		m_background->SetActive(true);
		break;
	case UIView::ViewStates::Visible:
		break;
	case UIView::ViewStates::AnimatingOut:
		m_currentViewState = ViewStates::NotVisible;
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

	delete m_mainMenuView;
	m_mainMenuView = nullptr;

	delete m_titleScreenView;
	m_titleScreenView = nullptr;

	delete m_background;
	m_background = nullptr;
}

void UIFrontEndView::TransitionIn(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition In: UI Front End View {} animation.", isAnimating ? "with" : "without"));

	m_currentViewState = UIView::ViewStates::AnimatingIn;
	m_background->SetActive(true);
	m_isActive = true;
}

void UIFrontEndView::TransitionOut(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition Out: UI Front End View {} animation.", isAnimating ? "with" : "without"));

	m_currentViewState = UIView::ViewStates::AnimatingOut;
}
