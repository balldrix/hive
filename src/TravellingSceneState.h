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
	TravellingSceneState(const std::string &name);
	TravellingSceneState(const TravellingSceneState&);
	TravellingSceneState& operator=(const TravellingSceneState&);
};
