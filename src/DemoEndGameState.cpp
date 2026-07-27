#include "DemoEndGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "MenuSystem.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

DemoEndGameState::DemoEndGameState() :
	GameState(DemoEnd)
{
}

DemoEndGameState::DemoEndGameState(GameStateManager* gameStateManager) : DemoEndGameState()
{
	m_gameStateManager = gameStateManager;
}

DemoEndGameState::~DemoEndGameState()
{
}

void DemoEndGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
	MenuSystem::Update();
}

void DemoEndGameState::Render(Graphics* graphics)
{
	GameState* gameplayState = m_gameStateManager->GetState(Gameplay);

	if(gameplayState) gameplayState->Render(graphics);
}
