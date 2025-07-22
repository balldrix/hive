#include "TitleScreenGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "Input.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

TitleScreenGameState::TitleScreenGameState() :
	m_graphics(nullptr),
	GameState(TitleScreen)
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

	auto input = m_gameStateManager->GetInput();
	auto buttons = input->GetGamePadButtons();

	if(input->WasKeyPressed(ENTER_KEY) || input->WasGamePadButtonPressed(buttons.a))
	{
		m_gameStateManager->SwitchState(MainMenu);
	}
}

void TitleScreenGameState::Render()
{
	UIManager::Render(m_graphics);
}
