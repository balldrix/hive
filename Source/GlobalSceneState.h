// GlobalSceneState.h
// Christopher Ball 2019-2020
// The global scene state during gameplay

#pragma once

#include "State.h"

class GameplayGameState;

class GlobalSceneState : public State<GameplayGameState>
{
public:
	static GlobalSceneState* Instance();

	virtual void OnEnter(GameplayGameState* game);
	virtual void Execute(GameplayGameState* game);
	virtual void OnExit(GameplayGameState* game);

private:
	GlobalSceneState() {}
	~GlobalSceneState() {}
	GlobalSceneState(std::string name);
	GlobalSceneState(const GlobalSceneState&);
	GlobalSceneState& operator=(const GlobalSceneState&);
};