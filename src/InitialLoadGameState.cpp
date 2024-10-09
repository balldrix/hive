#include "InitialLoadGameState.h"
#include "AssetLoader.h"
#include "Logger.h"
#include "GameStateManager.h"

InitialLoadGameState::InitialLoadGameState() : 
	GameState("InitialLoad")
{
}

InitialLoadGameState::InitialLoadGameState(GameStateManager* gameStateManager) : InitialLoadGameState()
{
	m_gameStateManager = gameStateManager;
}

InitialLoadGameState::~InitialLoadGameState()
{
}

void InitialLoadGameState::OnEntry()
{
	LoadAssets();
}

void InitialLoadGameState::OnExit()
{
}

void InitialLoadGameState::Update(float deltaTime)
{
	//AssetLoader::LoadAllPrewarmedAssets();

	//if (AssetLoader::IsLoadingDone())
		//LoadingState::TargetState = TitleScreenState.Instance;
		//m_gameStateManager->SwitchState("LoadingState");
}

void InitialLoadGameState::Render()
{
}

void InitialLoadGameState::ReleaseAll()
{
}

void InitialLoadGameState::LoadAssets()
{
	Logger::LogInfo("Loading Initial Game Assets");
	AssetLoader::PreWarmAssetsWithTag("initial_loading_assets");
}

void InitialLoadGameState::DeleteAssets()
{
}
