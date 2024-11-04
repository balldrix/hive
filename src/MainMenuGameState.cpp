#include "MainMenuGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "MenuSystem.h"
#include "UIManager.h"

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
	MenuSystem::Update(m_gameStateManager->GetInput());
}

void MainMenuGameState::Render()
{
	UIManager::Render(m_gameStateManager->GetGraphics());
}
