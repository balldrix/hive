#pragma once

#include "GameState.h"

class GameStateManager;

class FrontEndOptionsGameState : public GameState
{
public:
	FrontEndOptionsGameState();
	FrontEndOptionsGameState(GameStateManager* gameStateManager);
	~FrontEndOptionsGameState();

	void Update(float deltaTime) override;
	void Render() override;
};