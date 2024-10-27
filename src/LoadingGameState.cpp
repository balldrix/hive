#include "LoadingGameState.h"

#include "GameStateManager.h"
#include "Graphics.h"
#include "UIManager.h"
#include "AssetLoader.h"
#include "UIConfig.h"
#include "GameplayGameState.h"

LoadingGameState* LoadingGameState::s_instance = nullptr;
GameState* LoadingGameState::s_targetGameState = nullptr;
bool LoadingGameState::s_isLoadingToMainGameplay = false;

LoadingGameState::LoadingGameState() :
	m_graphics(nullptr),
	GameState("Loading")
{
	s_instance = this;
}

LoadingGameState::LoadingGameState(GameStateManager* gameStateManager) : LoadingGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = gameStateManager->GetGraphics();
}

LoadingGameState::~LoadingGameState()
{
	s_instance = nullptr;
}

void LoadingGameState::OnEntry()
{
	m_timer = 1.0f; // fake loading time
	
	if(!s_isLoadingToMainGameplay)
	{
		AssetLoader::PreWarmAssetsWithTag("front_end_assets");
	}
	else
	{
		s_targetGameState = m_gameStateManager->GetState("Gameplay");
	}
}

void LoadingGameState::Update(float deltaTime)
{
	if(!AssetLoader::IsLoadingDone())
	{
		AssetLoader::LoadAllPrewarmedAssets();
		return;
	}
	
	UIManager::Update(deltaTime);

	m_timer -= deltaTime;

	if(m_timer <= 0.0f)
		m_gameStateManager->SwitchState("FadeTransition");
}

void LoadingGameState::Render()
{
	UIManager::Render(m_graphics);
}

void LoadingGameState::OnExit()
{
	if (!s_isLoadingToMainGameplay)
	{
		UIManager::CreateUIFrontEndView();
	}
}

void LoadingGameState::SetTargetGameState(GameState* gamestate)
{
	s_targetGameState = gamestate;
}

void LoadingGameState::ProceedToFrontEnd()
{
	UIConfig::Init();
	UIManager::CreateUISystemView();
	s_isLoadingToMainGameplay = false;
	LoadingGameState::SetTargetGameState(s_instance->m_gameStateManager->GetState("TitleScreen"));
	s_instance->m_gameStateManager->SwitchState("Loading");
}

void LoadingGameState::ProceedToGameplay()
{
	s_isLoadingToMainGameplay = true;
	LoadingGameState::SetTargetGameState(s_instance->m_gameStateManager->GetState("Loading"));
	s_instance->m_gameStateManager->SwitchState("FadeTransition");
}