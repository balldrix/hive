#pragma once

#include "GameState.h"

class GameStateManager;

class MainMenuGameState : public GameState
{
public:
	MainMenuGameState();
	MainMenuGameState(GameStateManager* gameStateManager);
	~MainMenuGameState();

	void Update(float deltaTime) override;
	void Render() override;
};