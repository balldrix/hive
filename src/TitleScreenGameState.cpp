#include "TitleScreenGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "Input.h"
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

	if(m_gameStateManager->GetInput()->WasKeyPressed(ENTER_KEY))
	{
		m_gameStateManager->SwitchState("MainMenu");
	}
}

void TitleScreenGameState::Render()
{
	UIManager::Render(m_graphics);
}
