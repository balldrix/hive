#pragma once

#include "GameState.h"

class MainMenuGameState : public GameState
{
public:
	MainMenuGameState();
	MainMenuGameState(GameStateManager* gameStateManager);
	~MainMenuGameState();

	void Update(float deltaTime);
	void Render();
};

