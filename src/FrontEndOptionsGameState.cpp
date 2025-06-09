#include "FrontEndOptionsGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "MenuSystem.h"
#include "UIManager.h"

FrontEndOptionsGameState::FrontEndOptionsGameState() :
	GameState("FrontEndOptions")
{
}

FrontEndOptionsGameState::FrontEndOptionsGameState(GameStateManager* gameStateManager) : FrontEndOptionsGameState()
{
	m_gameStateManager = gameStateManager;
}

FrontEndOptionsGameState::~FrontEndOptionsGameState()
{

}

void FrontEndOptionsGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
	MenuSystem::Update(m_gameStateManager->GetInput());
}

void FrontEndOptionsGameState::Render()
{
	UIManager::Render(m_gameStateManager->GetGraphics());
}
