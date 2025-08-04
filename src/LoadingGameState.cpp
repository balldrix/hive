#include "LoadingGameState.h"

#include "AssetLoader.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "UIConfig.h"
#include "UIManager.h"

LoadingGameState* LoadingGameState::s_instance = nullptr;
GameState* LoadingGameState::s_targetGameState = nullptr;
bool LoadingGameState::isloadingFromMainGameplayToFrontend = false;
bool LoadingGameState::s_isLoadingToMainGameplay = false;

using namespace GameStateNameLibrary;

LoadingGameState::LoadingGameState() :
	m_timer(0.0f),
	m_isDone(false),
	GameState(Loading)
{
	s_instance = this;
}

LoadingGameState::LoadingGameState(GameStateManager* gameStateManager) : LoadingGameState()
{
	m_gameStateManager = gameStateManager;
}

LoadingGameState::~LoadingGameState()
{
	s_instance = nullptr;
}

void LoadingGameState::OnEntry()
{
	m_timer = 1.0f; // fake loading time
	m_isDone = false;

	if(!s_isLoadingToMainGameplay)
	{
		if(isloadingFromMainGameplayToFrontend)
		{
			AssetLoader::CleanupAssetsWithTag("ui_assets");
			AssetLoader::CleanupAssetsWithTag("gameplay_assets");
		}

		AssetLoader::PreWarmAssetsWithTag("front_end_assets");
	}
	else
	{
		s_targetGameState = m_gameStateManager->GetState("Gameplay");

		AssetLoader::CleanupAssetsWithTag("front_end_assets");
		AssetLoader::PreWarmAssetsWithTag("gameplay_assets");
		AssetLoader::PreWarmAssetsWithTag("ui_assets");
	}
}

void LoadingGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);

	m_timer -= deltaTime;

	if(m_timer > 0.0f || UIManager::IsFading()) return;

	if(!AssetLoader::IsLoadingDone())
	{
		AssetLoader::LoadAllPrewarmedAssets();
		return;
	}
	
	if(!m_isDone)
	{
		m_gameStateManager->GetState(s_targetGameState->GetStateName())->LoadAssets();
		m_isDone = true;
		return;
	}

	m_gameStateManager->SwitchState(FadeTransition);
}

void LoadingGameState::Render(Graphics* graphics)
{
	UIManager::Render(graphics);
}

void LoadingGameState::OnExit()
{
	if(!s_isLoadingToMainGameplay)
	{
		if(isloadingFromMainGameplayToFrontend)
		{
			UIManager::DestroyUIMainView();
		}

		UIManager::DestroyUIMainView();
		UIManager::CreateUIFrontEndView();
	}
	else
	{
		UIManager::DestroyUIFrontEndView();
		UIManager::CreateUIMainView();
	}
}

void LoadingGameState::SetTargetGameState(GameState* gamestate)
{
	s_targetGameState = gamestate;
}

void LoadingGameState::ProceedToFrontEnd()
{
	if(!isloadingFromMainGameplayToFrontend)
	{
		UIConfig::Init();
		UIManager::CreateUISystemView();
	}

	s_isLoadingToMainGameplay = false;
	LoadingGameState::SetTargetGameState(s_instance->m_gameStateManager->GetState(TitleScreen));
	s_instance->m_gameStateManager->SwitchState(Loading);
}

void LoadingGameState::ProceedToGameplay()
{
	s_isLoadingToMainGameplay = true;
	LoadingGameState::SetTargetGameState(s_instance->m_gameStateManager->GetState(Loading));
	s_instance->m_gameStateManager->SwitchState(FadeTransition);
}