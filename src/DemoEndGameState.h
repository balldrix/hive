#pragma once

#include "GameState.h"

class GameStateManager;
class Graphics;

class DemoEndGameState : public GameState
{
public:
	DemoEndGameState();
	DemoEndGameState(GameStateManager* gameStateManager);
	~DemoEndGameState();

	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
};