// EncounterSceneState.h
// Christopher Ball 2019-2020
// Deals with encounters during gameplay

#pragma once

#include "State.h"
#include "GameplayGameState.h"

class EncounterSceneState : public State<GameplayGameState>
{
public:
	static EncounterSceneState* Instance();

	virtual void OnEnter(GameplayGameState* game);
	virtual void Execute(GameplayGameState* game);
	virtual void OnExit(GameplayGameState* game);

private:
	EncounterSceneState() {}
	~EncounterSceneState() {}
	EncounterSceneState(std::string name);
	EncounterSceneState(const EncounterSceneState&);
	EncounterSceneState& operator=(const EncounterSceneState&);
};

