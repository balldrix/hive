#include "MainMenuGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "MenuSystem.h"
#include "UIManager.h"

MainMenuGameState* MainMenuGameState::s_instance = nullptr;

MainMenuGameState::MainMenuGameState() :
	GameState("MainMenu")
{
}

MainMenuGameState::MainMenuGameState(GameStateManager* gameStateManager) : MainMenuGameState()
{
	s_instance = this;
	m_gameStateManager = gameStateManager;
}

MainMenuGameState::~MainMenuGameState()
{
	s_instance = nullptr;
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

void MainMenuGameState::ProceedToOptionsState()
{
	s_instance->m_gameStateManager->SwitchState("OptionsState");
}
