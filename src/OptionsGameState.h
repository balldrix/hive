#pragma once

#include "GameState.h"
#include "GameStateManager.h"

class OptionsGameState : public GameState
{
public:
	OptionsGameState();
	OptionsGameState(GameStateManager* gameStateManager);
};