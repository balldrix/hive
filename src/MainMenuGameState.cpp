#include "MainMenuGameState.h"

#include "UIManager.h"
#include "GameStateManager.h"

MainMenuGameState::MainMenuGameState() :
	GameState("MainMenu")
{
}

MainMenuGameState::MainMenuGameState(GameStateManager* gameStateManager) : MainMenuGameState()
{
	m_gameStateManager = gameStateManager;
}

MainMenuGameState::~MainMenuGameState()
{
}

void MainMenuGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
}

void MainMenuGameState::Render()
{
	UIManager::Render(m_gameStateManager->GetGraphics());
}
