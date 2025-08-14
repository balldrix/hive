#pragma once

#include "GameState.h"

class GameStateManager;

class InitialLoadGameState : public GameState
{
public:
	InitialLoadGameState();
	InitialLoadGameState(GameStateManager* gameStateManager);
	virtual ~InitialLoadGameState() {};

	void OnEntry();
	void Update(float deltaTime);

private:
	void Setup();
};