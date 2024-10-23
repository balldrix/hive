#include "MainMenuGameState.h"

#include "UIManager.h"
#include "GameStateManager.h"

#include "Input.h"

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

	if(m_gameStateManager->GetInput()->WasKeyPressed(ESC_KEY))
		PostQuitMessage(0);
}

void MainMenuGameState::Render()
{
	UIManager::Render(m_gameStateManager->GetGraphics());
}
