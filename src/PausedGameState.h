#pragma once

#include "GameState.h"

class GameStateManager;

class PausedGameState : public GameState
{
public:
	PausedGameState();
	PausedGameState(GameStateManager* gameStateManager);
	~PausedGameState();

	void Update(float deltaTime) override;
	void Render() override;
};