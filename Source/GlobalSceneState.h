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
	GlobalSceneState(const std::string &name);
	GlobalSceneState(const GlobalSceneState&);
	GlobalSceneState& operator=(const GlobalSceneState&);
};