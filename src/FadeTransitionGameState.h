#pragma once

#include "GameState.h"

class Graphics;

class FadeTransitionGameState : public GameState
{
public:
	FadeTransitionGameState();
	FadeTransitionGameState(GameStateManager* gameStateManager);
	virtual ~FadeTransitionGameState() {};

	void OnEntry() override;
	void Update(float deltaTime) override;
	void Render(Graphics* graphics) override;
	void OnExit() override;
};