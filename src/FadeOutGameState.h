#pragma once

#include "GameState.h"

class Graphics;

class FadeOutGameState : public GameState
{
public:
	FadeOutGameState();
	FadeOutGameState(GameStateManager* gameStateManager);
	virtual ~FadeOutGameState();

	void OnEntry();
	void Update(float deltaTime);
	void Render();
	void OnExit();
private:
	Graphics* m_graphics;
};