#include "UIPlayerStatsView.h"

#include "AssetLoader.h"
#include "Logger.h"
#include "UIBarView.h"
#include "UIKillCount.h"
#include "UIManager.h"
#include "UIPortraitView.h"
#include "UIView.h"

#include <algorithm>
#include <cmath>
#include <directxtk/SimpleMath.h>
#include <string>

UIPlayerStatsView::UIPlayerStatsView() :
	m_portraitView(nullptr),
	m_healthBar(nullptr),
	m_specialBar(nullptr),
	m_killCount(nullptr)
{
}

UIPlayerStatsView::~UIPlayerStatsView()
{
	Shutdown();
}

void UIPlayerStatsView::Init(std::string name)
{
	const Color BackgroundColour = Color(0.525f, 0.509f, 0.603f);
	m_name = name;

	m_portraitViewStartPosition = Vector2(2.0f, 116.0f);
	m_portraitView = new UIPortraitView();
	m_portraitView->Init("Player Portrait");
	m_portraitView->SetPortraitTexture(AssetLoader::GetTexture("t_player_portrait"));
	m_portraitView->SetPosition(m_portraitViewStartPosition);
	m_portraitView->SetActive(true);

	UIManager::RegisterUIView(m_portraitView);

	m_healthBarStartPosition = Vector2(24.0f, 117.0f);
	m_healthBar = new UIBarView();
	m_healthBar->SetWidth(95);
	m_healthBar->Init("Player Health Bar");
	m_healthBar->SetFrameTexture(AssetLoader::GetTexture("t_bar_frame_player_health"));
	m_healthBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_healthBar->SetBackgroundColour(BackgroundColour);
	m_healthBar->SetFillTexture(AssetLoader::GetTexture("t_bar_fill_green"));
	m_healthBar->SetPosition(m_healthBarStartPosition);
	m_healthBar->SetActive(true);
	
	UIManager::RegisterUIView(m_healthBar);

	m_specialBarStartPosition = Vector2(24.0f, 125.0f);
	m_specialBar = new UIBarView();
	m_specialBar->SetHeight(10);
	m_specialBar->SetWidth(63);
	m_specialBar->Init("Player Special Bar");
	m_specialBar->SetFrameTexture(AssetLoader::GetTexture("t_bar_frame_player_special"));
	m_specialBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_specialBar->SetBackgroundColour(BackgroundColour);
	m_specialBar->SetFillTexture(AssetLoader::GetTexture("t_bar_fill_yellow"));
	m_specialBar->SetPosition(m_specialBarStartPosition);
	m_specialBar->SetActive(true);

	UIManager::RegisterUIView(m_specialBar);

	m_killCountStartPosition = Vector2(236.0f, 122.0f);
	m_killCount = new UIKillCount();
	m_killCount->Init("Player Kill Count");
	m_killCount->SetPosition(m_killCountStartPosition);
	m_killCount->SetActive(true);

	UIManager::RegisterUIView(m_killCount);
	UIManager::RegisterUIView(this);
}

void UIPlayerStatsView::Update(float deltaTime)
{
	if(!m_isActive) return;

	switch(m_currentViewState)
	{
	case ViewStates::AnimatingOut:
	case ViewStates::AnimatingIn:
		DoTransition(deltaTime);
		break;
	default:
		break;
	}
}

void UIPlayerStatsView::ForceHide(bool isForced)
{
	m_portraitView->ForceHide(isForced);
	m_healthBar->ForceHide(isForced);
	m_specialBar->ForceHide(isForced);
	m_killCount->ForceHide(isForced);
}

void UIPlayerStatsView::Shutdown()
{
	Logger::LogInfo("Shutting down UI PlayerInfoView");

	UIManager::UnregisterUIView(this);
	UIManager::UnregisterUIView(m_killCount);
	UIManager::UnregisterUIView(m_specialBar);
	UIManager::UnregisterUIView(m_healthBar);
	UIManager::UnregisterUIView(m_portraitView);

	delete m_killCount;
	m_killCount = nullptr;

	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_portraitView;
	m_portraitView = nullptr;
}

void UIPlayerStatsView::TransitionIn(bool isAnimating)
{
	m_isActive = true;
	m_portraitView->SetActive(true);
	m_healthBar->SetActive(true);
	m_specialBar->SetActive(true);
	m_killCount->SetActive(true);

	if(m_currentViewState == ViewStates::AnimatingIn ||
		m_currentViewState == ViewStates::Visible) return;

	if(isAnimating)
	{
		m_isAnimating = true;
		m_currentViewState = ViewStates::AnimatingIn;
		m_transitionTimer = TransitionInDuration;
	}
	else
	{
		m_currentViewState = ViewStates::Visible;
	}
}

void UIPlayerStatsView::TransitionOut(bool isAnimating)
{
	if(!isAnimating)
	{
		m_isAnimating = false;
		m_isActive = false;
		m_currentViewState = ViewStates::NotVisible;
		m_portraitView->SetActive(false);
		m_healthBar->SetActive(false);
		m_specialBar->SetActive(false);
		m_killCount->SetActive(false);
		return;
	}

	if(m_currentViewState == ViewStates::AnimatingOut ||
		m_currentViewState == ViewStates::NotVisible) return;

	m_isAnimating = true;
	m_currentViewState = ViewStates::AnimatingOut;
	m_transitionTimer = TransitionOutDuration;
}

void UIPlayerStatsView::DoTransition(float deltaTime)
{
	bool isAnimatingIn = m_currentViewState == ViewStates::AnimatingIn;

	if(m_transitionTimer > 0)
	{
		float duration = 1.0f + (isAnimatingIn ? TransitionInDuration : TransitionOutDuration);
		float t = std::clamp(m_transitionTimer / duration, 0.0f, 1.0f);
		if(!isAnimatingIn) t = 1 - t;

		float yOffset = std::lerp(0.0f, 20.0f, t);

		Vector2 portraitViewPosition = m_portraitViewStartPosition;
		portraitViewPosition.y = m_portraitViewStartPosition.y + yOffset;
		m_portraitView->SetPosition(portraitViewPosition);

		Vector2 healthBarPosition = m_healthBarStartPosition;
		healthBarPosition.y = m_healthBarStartPosition.y + yOffset;
		m_healthBar->SetPosition(healthBarPosition);

		Vector2 specialBarPosition = m_specialBarStartPosition;
		specialBarPosition.y = m_specialBarStartPosition.y + yOffset;
		m_specialBar->SetPosition(specialBarPosition);

		Vector2 killCountPosition = m_killCountStartPosition;
		killCountPosition.y = m_killCountStartPosition.y + yOffset;
		m_killCount->SetPosition(killCountPosition);

		m_transitionTimer -= deltaTime;
		return;
	}

	m_currentViewState = isAnimatingIn ? ViewStates::Visible : ViewStates::NotVisible;
	m_portraitView->SetActive(isAnimatingIn);
	m_healthBar->SetActive(isAnimatingIn);
	m_specialBar->SetActive(isAnimatingIn);
	m_killCount->SetActive(isAnimatingIn);
	m_isActive = isAnimatingIn;
	m_isAnimating = false;
}
