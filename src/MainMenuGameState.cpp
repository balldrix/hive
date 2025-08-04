#include "MainMenuGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "Graphics.h"
#include "MenuSystem.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

MainMenuGameState::MainMenuGameState() :
	GameState(MainMenu)
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
	MenuSystem::Update();
}

void MainMenuGameState::Render(Graphics* graphics)
{
	UIManager::Render(graphics);
}