#pragma once

#include "GameState.h"

class GameStateManager;
class Graphics;

class GameOverGameState : public GameState
{
public:
	GameOverGameState();
	GameOverGameState(GameStateManager* gameStateManager);
	~GameOverGameState();

	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
};