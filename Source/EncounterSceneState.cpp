#include "EncounterSceneState.h"

#include "GameplayGameState.h"
#include "InGameHudManager.h"
#include "Camera.h"

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

	game->SetPlayerBoundaryX(cameraPositionX, cameraPositionX + cameraWidth);
}

void EncounterSceneState::Execute(GameplayGameState* game)
{
}

void EncounterSceneState::OnExit(GameplayGameState* game)
{
}
