#pragma once

#include "GameState.h"

class GameStateManager;
class Graphics;

class TitleScreenGameState : public GameState
{
public:
	TitleScreenGameState();
	TitleScreenGameState(GameStateManager* gameStateManager);
	virtual	~TitleScreenGameState();

	void Update(float deltaTime);
	void Render();

private:
	Graphics* m_graphics;
};