#include "EncounterSceneState.h"

#include "Camera.h"
#include "EncounterHandler.h"
#include "GameOverSceneState.h"
#include "GameplayGameState.h"
#include "StateMachine.h"
#include "TravellingSceneState.h"

EncounterSceneState* EncounterSceneState::Instance()
{
	static EncounterSceneState instance;
	return &instance;
}

void EncounterSceneState::OnEnter(GameplayGameState* game)
{
	game->GetCamera()->SetTarget(nullptr);

	float cameraPositionX = game->GetCamera()->GetPosition().x;
	float cameraWidth = game->GetCamera()->GetWidth();

	game->UpdateGameBounds(cameraPositionX, cameraPositionX + cameraWidth);
}

void EncounterSceneState::Execute(GameplayGameState* game)
{
}

void EncounterSceneState::OnExit(GameplayGameState* game)
{
}
