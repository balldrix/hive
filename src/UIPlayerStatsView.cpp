#include "UIPlayerStatsView.h"

#include "AssetLoader.h"
#include "Logger.h"
#include "UIBarView.h"
#include "UIManager.h"
#include "UIKillCount.h"
#include "UIPortraitView.h"
#include "UIView.h"

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

	m_portraitView = new UIPortraitView();
	m_portraitView->Init("Player Portrait");
	m_portraitView->SetPosition(Vector2(2.0f, 116.0f));

	m_healthBar = new UIBarView();
	m_healthBar->SetWidth(95);
	m_healthBar->Init("Player Health Bar");
	m_healthBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_healthBar->SetBackgroundColour(BackgroundColour);
	m_healthBar->SetFillTexture(AssetLoader::GetTexture("t_bar_fill_green"));
	m_healthBar->SetFrameTexture(AssetLoader::GetTexture("t_bar_frame_player_health"));
	m_healthBar->SetPosition(Vector2(24.0f, 117.0f));
	
	UIManager::RegisterUIView(m_healthBar);

	m_specialBar = new UIBarView();
	m_specialBar->SetWidth(63);
	m_specialBar->Init("Player Special Bar");
	m_specialBar->SetBackgroundTexture(AssetLoader::GetTexture("t_pixel"));
	m_specialBar->SetBackgroundColour(BackgroundColour);
	m_specialBar->SetFillTexture(AssetLoader::GetTexture("t_bar_fill_yellow"));
	m_specialBar->SetFrameTexture(AssetLoader::GetTexture("t_bar_frame_player_special"));
	m_specialBar->SetPosition(Vector2(24.0f, 125.0f));

	UIManager::RegisterUIView(m_specialBar);

	m_killCount = new UIKillCount();
	m_killCount->Init("Player Kill Count");

	UIManager::RegisterUIView(m_killCount);
}

void UIPlayerStatsView::Update(float deltaTime)
{
}

void UIPlayerStatsView::Render(Graphics* graphics)
{
	m_portraitView->Render(graphics);
}

void UIPlayerStatsView::TransitionIn(bool isAnimating)
{
}

void UIPlayerStatsView::TransitionOut(bool isAnimating)
{
}

void UIPlayerStatsView::Shutdown()
{
	Logger::LogInfo("Shutting down UI PlayerInfoView");

	UIManager::UnregisterUIView(m_healthBar);
	UIManager::UnregisterUIView(m_killCount);

	delete m_killCount;
	m_killCount = nullptr;

	delete m_healthBar;
	m_healthBar = nullptr;

	delete m_portraitView;
	m_portraitView = nullptr;
}

void UIPlayerStatsView::DoTransition(float deltaTime)
{
}
