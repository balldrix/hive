#include "GameOverSceneState.h"

#include "GameplayGameState.h"
#include "GameOverScreenController.h"

GameOverSceneState* GameOverSceneState::Instance()
{
    static GameOverSceneState instance;
    return &instance;
}

void GameOverSceneState::OnEnter(GameplayGameState* game)
{
    game->GetGameOverScreenController()->EnableWinScreen();
}

void GameOverSceneState::Execute(GameplayGameState* game)
{
}

void GameOverSceneState::OnExit(GameplayGameState* game)
{
}
