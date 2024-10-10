#include "LoadingGameState.h"

#include "GameStateManager.h"
#include "Graphics.h"
#include "UIManager.h"

GameState* LoadingGameState::s_targetGameState;

LoadingGameState::LoadingGameState() :
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

void LoadingGameState::Render()
{
	UIManager::RenderUI(m_graphics);
}