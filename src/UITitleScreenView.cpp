#include "UITitleScreenView.h"

#include "UISpriteText.h"
#include "UIImageView.h"
#include "Sprite.h"
#include "UIManager.h"
#include "Logger.h"
#include "UIConfig.h"
#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "Sprite.h"

using namespace GlobalConstants;

UITitleScreenView::UITitleScreenView() :
	m_startGameText(nullptr),
	m_logoImage(nullptr)
{
}

UITitleScreenView::~UITitleScreenView()
{
	Shutdown();
}

void UITitleScreenView::Init(std::string name)
{
	m_name = name;
	m_startGameText = new UISpriteText();
	m_startGameText->Init(UIConfig::DespairFont8);

	// TODO check inputs for controller 
	m_startGameText->SetText("Press Enter To Start");
	m_startGameText->SetPosition(Vector2(GameWidth / 2.0f, GameHeight - 10.0f));
	m_startGameText->SetActive(true);
	m_startGameText->SetAlignment(UISpriteText::Alignments::Centre);

	m_logoImage = new UIImageView();
	m_logoImage->Init("Title Logo");
	m_logoImage->GetSprite()->Init(AssetLoader::GetTexture("t_title_logo"));
	m_logoImage->SetPosition(Vector2(GameWidth - 20.0f, 40.0f));
	m_logoImage->SetOrigin(Vector2((float)m_logoImage->GetSprite()->GetWidth(), 0.0f));
	m_logoImage->SetDepth(0.9f);
	m_logoImage->TransitionOut(false);

	UIManager::RegisterUIView(this);
}

void UITitleScreenView::Render(Graphics* graphics)
{
	if(!m_isActive) return;

	m_startGameText->Render(graphics);
	m_logoImage->Render(graphics);
}

void UITitleScreenView::Update(float deltaTime)
{
	if (!m_isActive) return;

	switch (m_currentViewState)
	{
	case UIView::ViewStates::NotVisible:
		break;
	case UIView::ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
		m_startGameText->SetActive(true);
		m_logoImage->SetActive(true);
		break;
	case UIView::ViewStates::Visible:
		break;
	case UIView::ViewStates::AnimatingOut:
		m_currentViewState = ViewStates::NotVisible;
		m_startGameText->SetActive(false);
		m_isActive = false;
		break;
	default:
		break;
	}
}

void UITitleScreenView::TransitionIn(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition In: UI Title Screen View {} animation.", isAnimating ? "with" : "without"));

	m_isActive = true;

	if(isAnimating)
	{
		m_currentViewState = UIView::ViewStates::AnimatingIn;
		return;
	}

	m_currentViewState = UIView::ViewStates::Visible;
}

void UITitleScreenView::TransitionOut(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition Out: UI Title Screen View {} animation.", isAnimating ? "with" : "without"));

	if (isAnimating)
	{
		m_currentViewState = UIView::ViewStates::AnimatingOut;
		return;
	}

	m_currentViewState = UIView::ViewStates::NotVisible;
	m_startGameText->SetActive(false);
	m_isActive = false;
}

void UITitleScreenView::Shutdown()
{
	Logger::LogInfo("Shutting down UI Title Screen View");

	UIManager::UnregisterUIView(this);

	delete m_startGameText;
	m_startGameText = nullptr;
}
