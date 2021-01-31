// TravellingSceneState.h
// Christopher Ball 2019-2021
// Deals with travel between encounters

#pragma once

#include "State.h"

class GameplayGameState;

class TravellingSceneState : public State<GameplayGameState>
{
public:
	static TravellingSceneState* Instance();

	virtual void OnEnter(GameplayGameState* game);
	virtual void Execute(GameplayGameState* game);
	virtual void OnExit(GameplayGameState* game);

private:
	TravellingSceneState() {}
	~TravellingSceneState() {}
	TravellingSceneState(std::string name);
	TravellingSceneState(const TravellingSceneState&);
	TravellingSceneState& operator=(const TravellingSceneState&);
};
