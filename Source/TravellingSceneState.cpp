#include "TravellingSceneState.h"

#include "GameplayGameState.h"
#include "Camera.h"
#include "Player.h"
#include "InGameHudManager.h"
#include "TravellingHandler.h"
#include "LevelRenderer.h"
#include "GlobalConstants.h"
#include "InGameHudConstants.h"

using namespace InGameHudConstants;
using namespace GlobalConstants;

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

	if(game->GetTravellingHandler()->GetTravelTimer() > TravelPromptTime)
		game->GetHudManager()->EnableTravelPrompt();
}

void TravellingSceneState::OnExit(GameplayGameState* game)
{
	game->GetTravellingHandler()->SetTravelTimer(0.0f);
	game->GetHudManager()->DisableTravelPrompt();
}