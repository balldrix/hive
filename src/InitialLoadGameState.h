#pragma once

#include "GameState.h"

class GameStateManager;

class InitialLoadGameState : public GameState
{
public:
	InitialLoadGameState();
	InitialLoadGameState(GameStateManager* gameStateManager);
	virtual ~InitialLoadGameState();

	void OnEntry();
	void OnExit();

	void Update(float deltaTime);
	
	void ReleaseAll();

private:
	void LoadAssets();
	void ProceedToFrontEnd();
};