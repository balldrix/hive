#include "TravellingSceneState.h"

#include "Camera.h"
#include "GameplayGameState.h"
#include "LevelRenderer.h"
#include "TravellingHandler.h"

TravellingSceneState* TravellingSceneState::Instance()
{
	static TravellingSceneState instance;
	return &instance;
}

void TravellingSceneState::OnEnter(GameplayGameState* game)
{
	game->GetCamera()->SetTarget(game->GetPlayer());
	game->GetCamera()->SetBoundary(game->GetCamera()->GetPosition().x);
	game->GetTravellingHandler()->SetTravelTimer(0.0f);
	game->SetPlayerBoundaryX(game->GetCamera()->GetPosition().x, 
		(float)game->GetLevelRenderer()->GetLevelPixelWidth());
}

void TravellingSceneState::Execute(GameplayGameState* game)
{
	game->CheckForEncounter();
	game->GetTravellingHandler()->Update(game->GetDeltaTime());

	// TODO move to UIManager
	//if(game->GetTravellingHandler()->GetTravelTimer() > TravelPromptTime)
	//	game->GetHudManager()->EnableTravelPrompt();
}

void TravellingSceneState::OnExit(GameplayGameState* game)
{
	game->GetTravellingHandler()->SetTravelTimer(0.0f);
}