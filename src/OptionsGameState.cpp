#include "OptionsGameState.h"

#include "GameStateManager.h"

OptionsGameState::OptionsGameState()
{
}

OptionsGameState::OptionsGameState(GameStateManager* gameStateManager)
{
	m_gameStateManager = gameStateManager;
}
