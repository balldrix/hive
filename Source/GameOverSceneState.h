#pragma once

#include "State.h"
#include "GameplayGameState.h"

class GameOverSceneState : public State<GameplayGameState>
{
public:
	static GameOverSceneState* Instance();

	virtual void OnEnter(GameplayGameState* game);
	virtual void Execute(GameplayGameState* game);
	virtual void OnExit(GameplayGameState* game);

private:
	GameOverSceneState() {}
	~GameOverSceneState() {}
	GameOverSceneState(std::string name);
	GameOverSceneState(const GameOverSceneState&);
	GameOverSceneState& operator=(const GameOverSceneState&);
};