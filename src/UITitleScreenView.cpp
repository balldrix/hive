#include "UITitleScreenView.h"

#include "AssetLoader.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "Logger.h"
#include "UIConfig.h"
#include "UIImageView.h"
#include "UIManager.h"
#include "UISpriteText.h"
#include "UIView.h"

#include <cmath>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>

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

	// @TODO check inputs for controller 
	m_startGameText->SetText("Press Enter To Start");
	m_startGameText->SetPosition(StartGameTextStartPosition);
	m_startGameText->SetActive(true);
	m_startGameText->SetAlignment(UISpriteText::Alignments::Centre);
	m_startGameText->SetDepth(0.5f);

	m_logoImage = new UIImageView();
	m_logoImage->Init("Title Logo", AssetLoader::GetTexture("t_title_logo"));
	m_logoImage->SetPosition(LogoImageStartPosition);
	m_logoImage->SetOrigin(Vector2((float)m_logoImage->GetSprite()->GetWidth(), 0.0f));
	m_logoImage->SetDepth(0.5f);
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
	case ViewStates::NotVisible:
		break;
	case ViewStates::AnimatingIn:
		m_currentViewState = ViewStates::Visible;
		m_startGameText->SetActive(true);
		m_logoImage->SetActive(true);
		break;
	case ViewStates::Visible:
		break;
	case ViewStates::AnimatingOut:
		DoTransition(deltaTime);
		break;
	default:
		break;
	}
}

void UITitleScreenView::DoTransition(float deltaTime)
{
	if(m_transitionTimer > 0)
	{
		float t = m_transitionTimer / TransitionDuration;
		float logoImageXPos = (float)(std::lerp(LogoImageStartPosition.x, GameWidth + m_logoImage->GetSprite()->GetWidth(), 1 - t));
		float lerpedAlpha = std::lerp(1.0f, 0.0f, 1 - t);
		Color colour = m_startGameText->GetColour();
		colour.A(lerpedAlpha);

		m_logoImage->SetPosition(Vector2(logoImageXPos, LogoImageStartPosition.y));
		m_startGameText->SetColour(colour);
		m_transitionTimer -= deltaTime;
		return;
	}

	m_currentViewState = ViewStates::NotVisible;
	m_startGameText->SetActive(false);
	m_logoImage->SetActive(false);
	m_isActive = false;
	m_isAnimating = false;
}

void UITitleScreenView::TransitionIn(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition In: UI Title Screen View {} animation.", isAnimating ? "with" : "without"));

	m_isAnimating = isAnimating;
	m_isActive = true;
	m_currentViewState = ViewStates::Visible;
	m_startGameText->SetActive(true);
	m_logoImage->SetActive(true);
}

void UITitleScreenView::TransitionOut(bool isAnimating)
{
	Logger::LogInfo(fmt::format("Transition Out: UI Title Screen View {} animation.", isAnimating ? "with" : "without"));

	if (isAnimating)
	{
		m_transitionTimer = TransitionDuration;
		m_currentViewState = ViewStates::AnimatingOut;
		return;
	}

	m_currentViewState = ViewStates::NotVisible;
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
