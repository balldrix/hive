#include "UIEnemyStatsView.h"

#include "AssetLoader.h"
#include "UIBarView.h"
#include "UIManager.h"
#include "UIPortraitView.h"
#include "UIView.h"

#include <directxtk/SimpleMath.h>
#include <string>

UIEnemyStatsView::UIEnemyStatsView() :
	m_portraitView(nullptr),
	m_healthBar(nullptr)
{
}

UIEnemyStatsView::~UIEnemyStatsView()
{
	Shutdown();
}

void UIEnemyStatsView::Init(std::string name)
{
	m_name = name;

	m_portraitView = new UIPortraitView();
	m_portraitView->Init("Enemy Portrait");
	m_portraitView->SetPosition(Vector2(2.0f, 2.0f));

	UIManager::RegisterUIView(m_portraitView);

	m_healthBar = new UIBarView();
	m_healthBar->Init("Enemy Health Bar");
	m_healthBar->SetWidth(95);
	m_healthBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_healthBar->SetBackgroundColour(Color(0.525f, 0.509f, 0.603f));
	m_healthBar->SetFillTexture(AssetLoader::GetTexture("t_bar_fill_red"));
	m_healthBar->SetFrameTexture(AssetLoader::GetTexture("t_bar_frame_enemy"));
	m_healthBar->SetPosition(Vector2(24.0f, 3.0f));

	UIManager::RegisterUIView(m_healthBar);
}/*

void UIEnemyStatsView::Update(float deltatime)
{
}

void UIEnemyStatsView::TransitionIn(bool isAnimating)
{
	m_isActive = true;

	if (m_currentViewState == ViewStates::AnimatingIn ||
		m_currentViewState == ViewStates::Visible) return;

	if (isAnimating)
	{
		m_isAnimating = true;
		m_currentViewState = ViewStates::AnimatingIn;
		m_transitionTimer = TransitionInDuration;
		m_offsetPosition = Vector2::Zero;
		m_targetOffsetPosition = Vector2(0.0f, 20.0f);
	}
	else
	{
		m_currentViewState = ViewStates::Visible;
		m_offsetPosition = Vector2::Zero;
		m_targetOffsetPosition = Vector2::Zero;
	}
}

void UIEnemyStatsView::TransitionOut(bool isAnimating)
{
}*/

void UIEnemyStatsView::ForceHide(bool isForced)
{
	m_portraitView->ForceHide(isForced);
	m_healthBar->ForceHide(isForced);
}

void UIEnemyStatsView::Shutdown()
{
	UIManager::UnregisterUIView(m_portraitView);
	UIManager::UnregisterUIView(m_healthBar);

	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_portraitView;
	m_portraitView = nullptr;
}

//void UIEnemyStatsView::DoTransition(float deltaTime)
//{
//}
