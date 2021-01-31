#include "EncounterSceneState.h"

#include "GameplayGameState.h"
#include "InGameHudManager.h"
#include "Camera.h"
#include "EncounterHandler.h"
#include "NPCManager.h"
#include "StateMachine.h"
#include "GameplayOwnedSceneStates.h"

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

	int index = game->GetEncounterHandler()->GetEncounterIndex();
	game->GetEncounterHandler()->SpawnEncounter();
}

void EncounterSceneState::Execute(GameplayGameState* game)
{
	EncounterHandler* encounterHandler = game->GetEncounterHandler();

	if(encounterHandler->GetIsEncounterDone() == false)
		return;
	
	encounterHandler->IncreaseEncounterIndex();

	if(encounterHandler->GetEncounterIndex() < encounterHandler->GetNumberOfEncounters())
		game->GetSceneStateMachine()->ChangeState(TravellingSceneState::Instance());

	if(encounterHandler->GetEncounterIndex() == encounterHandler->GetNumberOfEncounters())
		game->GetSceneStateMachine()->ChangeState(GameOverSceneState::Instance());
}

void EncounterSceneState::OnExit(GameplayGameState* game)
{
}
