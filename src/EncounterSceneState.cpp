#include "EncounterSceneState.h"

#include "GameplayGameState.h"
#include "Camera.h"
#include "EncounterHandler.h"
#include "StateMachine.h"
#include "TravellingSceneState.h"
#include "GameOverSceneState.h"

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
