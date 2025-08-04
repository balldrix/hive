#pragma once

#include "GameState.h"

class GameStateManager;
class Graphics;
class Input;

class TitleScreenGameState : public GameState
{
public:
	TitleScreenGameState();
	TitleScreenGameState(GameStateManager* gameStateManager, Input* input);
	~TitleScreenGameState();

	void Update(float deltaTime);
	void Render(Graphics* graphics);

private:
	Input* m_input;
};