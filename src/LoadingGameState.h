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

	static void ProceedToFrontEnd();
	static void ProceedToGameplay();

private:
	static LoadingGameState* s_instance;
	static GameState* s_targetGameState;
	static bool s_isLoadingToMainGameplay;
	static bool isloadingFromMainGameplayToFrontend;
	Graphics* m_graphics;
	float m_timer;
};