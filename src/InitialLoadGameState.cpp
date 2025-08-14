#include "InitialLoadGameState.h"

#include "AssetLoader.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "LoadingGameState.h"
#include "Logger.h"

using namespace GameStateNameLibrary;

InitialLoadGameState::InitialLoadGameState() : 
	GameState(InitialLoad)
{
}

InitialLoadGameState::InitialLoadGameState(GameStateManager* gameStateManager) : InitialLoadGameState()
{
	m_gameStateManager = gameStateManager;
}

void InitialLoadGameState::OnEntry()
{
	Setup();
}

void InitialLoadGameState::Update(float deltaTime)
{
	if(!AssetLoader::IsLoadingDone())
	{
		AssetLoader::LoadAllPrewarmedAssets();
	}
	else 
	{
		LoadingGameState::ProceedToFrontEnd();
	}
}

void InitialLoadGameState::Setup()
{
	Logger::LogInfo("Loading Initial Game Assets.");
	AssetLoader::PreWarmAssetsWithTag("initial_loading_assets");
}