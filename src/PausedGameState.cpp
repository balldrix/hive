#include "PausedGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "MenuSystem.h"
#include "UIManager.h"

PausedGameState::PausedGameState() :
	GameState("Paused")
{
}

PausedGameState::PausedGameState(GameStateManager* gameStateManager) : PausedGameState()
{
	m_gameStateManager = gameStateManager;
}

PausedGameState::~PausedGameState()
{
}

void PausedGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
	MenuSystem::Update(m_gameStateManager->GetInput());
}

void PausedGameState::Render()
{
	GameState* gameplayState = m_gameStateManager->GetPreviousState();

	if(gameplayState)
	{
		gameplayState->Render();
	}

	UIManager::Render(m_gameStateManager->GetGraphics());
}