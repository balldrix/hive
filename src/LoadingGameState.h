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

	void OnEntry();
	void Update(float deltaTime);
	void Render();
	void OnExit();

	static void SetTargetGameState(GameState* gamestate);
	static GameState* GetTargetGameState() { return s_targetGameState; }

	static void SetLoadingToMainGameplay(bool isLoadingToMainGameplay);
	static bool IsLoadingToMainGameplay() { return s_isLoadingToMainGameplay; }

private:
	Graphics* m_graphics;
	
	static GameState* s_targetGameState;
	static bool s_isLoadingToMainGameplay;
};