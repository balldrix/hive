#include "GameOverSceneState.h"

#include "GameplayGameState.h"

GameOverSceneState* GameOverSceneState::Instance()
{
    static GameOverSceneState instance;
    return &instance;
}

void GameOverSceneState::OnEnter(GameplayGameState* game)
{
}

void GameOverSceneState::Execute(GameplayGameState* game)
{
}

void GameOverSceneState::OnExit(GameplayGameState* game)
{
}
