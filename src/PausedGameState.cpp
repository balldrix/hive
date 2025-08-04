#include "PausedGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "MenuSystem.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

PausedGameState::PausedGameState() :
	GameState(Paused)
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
	MenuSystem::Update();
}

void PausedGameState::Render(Graphics* graphics)
{
	GameState* gameplayState = m_gameStateManager->GetState(Gameplay);

	if(gameplayState) gameplayState->Render(graphics);

	UIManager::Render(graphics);
}