#pragma once

#include "GameState.h"

class GameStateManager;
class Graphics;

class LoadingGameState : public GameState
{
public:
	LoadingGameState();
	LoadingGameState(GameStateManager* gameStateManager);
	virtual ~LoadingGameState();

	virtual void OnEntry() {};				
	virtual void OnExit() {};

	void Update(float deltaTime);
	void Render();

	static GameState* s_targetGameState;

private:
	Graphics* m_graphics;
};