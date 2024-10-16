#include "TitleScreenGameState.h"

#include "GameStateManager.h"
#include "UIManager.h"

TitleScreenGameState::TitleScreenGameState() :
	m_graphics(nullptr),
	GameState("TitleScreen")
{
}

TitleScreenGameState::TitleScreenGameState(GameStateManager* gameStateManager) : TitleScreenGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = gameStateManager->GetGraphics();
}

TitleScreenGameState::~TitleScreenGameState()
{
}

void TitleScreenGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);
}

void TitleScreenGameState::Render()
{
	UIManager::Render(m_graphics);
}
