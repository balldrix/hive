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

	void Render();

	static GameState* s_targetGameState;

private:
	Graphics* m_graphics;
};