#include "BeginSceneState.h"

#include "GameplayGameState.h"

StartingSceneState* StartingSceneState::Instance()
{
	static StartingSceneState instance;
	return &instance;
}

void StartingSceneState::OnEnter(GameplayGameState* game)
{
	game->Begin();
}

void StartingSceneState::Execute(GameplayGameState* game)
{
}

void StartingSceneState::OnExit(GameplayGameState* game)
{
}
