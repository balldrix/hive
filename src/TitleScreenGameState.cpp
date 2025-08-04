#include "TitleScreenGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "Graphics.h"
#include "Input.h"
#include "UIManager.h"

using namespace GameStateNameLibrary;

TitleScreenGameState::TitleScreenGameState() :
	m_input(nullptr),
	GameState(TitleScreen)
{
}

TitleScreenGameState::TitleScreenGameState(GameStateManager* gameStateManager, Input* input) : TitleScreenGameState()
{
	m_gameStateManager = gameStateManager;
	m_input = input;
}

TitleScreenGameState::~TitleScreenGameState()
{
}

void TitleScreenGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);

	auto buttons = m_input->GetGamePadButtons();

	if(m_input->WasKeyPressed(ENTER_KEY) || m_input->WasGamePadButtonPressed(buttons.a))
	{
		m_gameStateManager->SwitchState(MainMenu);
	}
}

void TitleScreenGameState::Render(Graphics* graphics)
{
	UIManager::Render(graphics);
}
