#include "GameOverGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "Graphics.h"
#include "MenuSystem.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

GameOverGameState::GameOverGameState() :
	GameState(GameOver)
{
}

GameOverGameState::GameOverGameState(GameStateManager* gameStateManager) : GameOverGameState()
{
	m_gameStateManager = gameStateManager;
}

GameOverGameState::~GameOverGameState()
{
}

void GameOverGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
	MenuSystem::Update();
}

void GameOverGameState::Render(Graphics* graphics)
{
	GameState* gameplayState = m_gameStateManager->GetState(Gameplay);

	if(gameplayState) gameplayState->Render(graphics);
}
