#pragma once

#include "GameState.h"

class GameStateManager;

class SharedOptionsGameState : public GameState
{
public:
	SharedOptionsGameState();
	SharedOptionsGameState(GameStateManager* gameStateManager);
	~SharedOptionsGameState();

	void Update(float deltaTime) override;
	void Render() override;
};