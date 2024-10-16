#pragma once

#include "GameState.h"

class Graphics;

class FadeTransitionGameState : public GameState
{
public:
	FadeTransitionGameState();
	FadeTransitionGameState(GameStateManager* gameStateManager);
	virtual ~FadeTransitionGameState() {};

	void OnEntry();
	void Update(float deltaTime);
	void Render();
	void OnExit();
private:
	Graphics* m_graphics;
};