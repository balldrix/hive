#include "InitialLoadGameState.h"
#include "AssetLoader.h"
#include "Logger.h"
#include "GameStateManager.h"
#include "LoadingGameState.h"
#include "UIManager.h"

InitialLoadGameState::InitialLoadGameState() : 
	GameState("InitialLoad")
{
}

InitialLoadGameState::InitialLoadGameState(GameStateManager* gameStateManager) : InitialLoadGameState()
{
	m_gameStateManager = gameStateManager;
}

void InitialLoadGameState::OnEntry()
{
	LoadAssets();
}

void InitialLoadGameState::Update(float deltaTime)
{
	if(!AssetLoader::IsLoadingDone())
	{
		AssetLoader::LoadAllPrewarmedAssets();
	}
	else 
	{
		ProceedToFrontEnd();
	}
}

void InitialLoadGameState::LoadAssets()
{
	Logger::LogInfo("Loading Initial Game Assets.");
	AssetLoader::PreWarmAssetsWithTag("initial_loading_assets");
}

void InitialLoadGameState::ProceedToFrontEnd()
{
	UIManager::CreateUISystemView();
	LoadingGameState::s_targetGameState = m_gameStateManager->GetState("TitleScreen");
	m_gameStateManager->SwitchState("Loading");
}