#include "TravellingSceneState.h"

#include "GameplayGameState.h"
#include "Camera.h"
#include "Player.h"
#include "InGameHudManager.h"
#include "TravellingHandler.h"

TravellingSceneState* TravellingSceneState::Instance()
{
	static TravellingSceneState instance;
	return &instance;
}

void TravellingSceneState::OnEnter(GameplayGameState* game)
{
	game->GetCamera()->SetTarget(game->GetPlayer());
	game->GetTravellingHandler()->SetTravelTimer(0.0f);
}

void TravellingSceneState::Execute(GameplayGameState* game)
{
	game->CheckForEncounter();
	game->GetTravellingHandler()->Update(game->GetDeltaTime());

	if(game->GetTravellingHandler()->GetTravelTimer() > 3.0f)
		game->GetHudManager()->EnableTravelPrompt();
}

void TravellingSceneState::OnExit(GameplayGameState* game)
{
}