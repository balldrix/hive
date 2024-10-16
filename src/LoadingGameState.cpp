#include "LoadingGameState.h"

#include "GameStateManager.h"
#include "Graphics.h"
#include "UIManager.h"
#include "AssetLoader.h"

GameState* LoadingGameState::s_targetGameState = nullptr;
bool LoadingGameState::s_isLoadingToMainGameplay = false;

LoadingGameState::LoadingGameState() :
	m_graphics(nullptr),
	GameState("Loading")
{
}

LoadingGameState::LoadingGameState(GameStateManager* gameStateManager) : LoadingGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = gameStateManager->GetGraphics();
}

LoadingGameState::~LoadingGameState()
{
	OnExit();
}

void LoadingGameState::OnEntry()
{
	if(!s_isLoadingToMainGameplay)
	{
		AssetLoader::PreWarmAssetsWithTag("front_end_assets");
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

	static float timer = 3.0f;
	timer -= deltaTime;

	if(timer <= 0.0f)
		m_gameStateManager->SwitchState("FadeOut");
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

void LoadingGameState::SetLoadingToMainGameplay(bool isLoadingToMainGameplay)
{
	s_isLoadingToMainGameplay = isLoadingToMainGameplay;
}
