#include "SharedOptionsGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "Graphics.h"
#include "MenuSystem.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

SharedOptionsGameState::SharedOptionsGameState() :
	GameState(SharedOptions)
{
}

SharedOptionsGameState::SharedOptionsGameState(GameStateManager* gameStateManager) : SharedOptionsGameState()
{
	m_gameStateManager = gameStateManager;
}

SharedOptionsGameState::~SharedOptionsGameState()
{

}

void SharedOptionsGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
	MenuSystem::Update();
}

void SharedOptionsGameState::Render(Graphics* graphics)
{
	UIManager::Render(graphics);

	GameState* previousGameState = m_gameStateManager->GetPreviousState();

	if(previousGameState->GetStateName() == Paused)
	{
		m_gameStateManager->GetState(Gameplay)->Render(graphics);
	}
}
