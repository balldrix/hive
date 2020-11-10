#include "GlobalSceneState.h"

#include "GameplayGameState.h"

GlobalSceneState* GlobalSceneState::Instance()
{
	static GlobalSceneState instance;
	return &instance;
}

void GlobalSceneState::OnEnter(GameplayGameState* game)
{
}

void GlobalSceneState::Execute(GameplayGameState* game)
{
	game->Tick(game->GetDeltaTime());
}

void GlobalSceneState::OnExit(GameplayGameState* game)
{
}
