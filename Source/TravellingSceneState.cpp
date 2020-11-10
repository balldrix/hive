#include "TravellingSceneState.h"

#include "GameplayGameState.h"
#include "Camera.h"
#include "Player.h"

TravellingSceneState* TravellingSceneState::Instance()
{
	static TravellingSceneState instance;
	return &instance;
}

void TravellingSceneState::OnEnter(GameplayGameState* game)
{
	game->GetCamera()->SetTarget(game->GetPlayer());
}

void TravellingSceneState::Execute(GameplayGameState* game)
{
	game->CheckForEncounter();
}

void TravellingSceneState::OnExit(GameplayGameState* game)
{
}
