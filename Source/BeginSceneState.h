// StartingSceneState.h
// Christopher Ball 2019-2020
// starting scene state

#pragma once

#include "State.h"

class GameplayGameState;

class StartingSceneState : public State<GameplayGameState>
{
public:
	static StartingSceneState* Instance();

	virtual void OnEnter(GameplayGameState* game);
	virtual void Execute(GameplayGameState* game);
	virtual void OnExit(GameplayGameState* game);

private:
	StartingSceneState() {}
	~StartingSceneState() {}
	StartingSceneState(std::string name);
	StartingSceneState(const StartingSceneState&);
	StartingSceneState& operator=(const StartingSceneState&);
};
