#pragma once

#include <string>
#include <vector>

class Graphics;
class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	static GameStateManager* Instance();

	void AddState(GameState* state);
	void SwitchState(std::string stateName);
	void ProceedToPreviousState();

	GameState* GetState(std::string stateName) const;
	GameState* GetCurrentState() const;
	GameState* GetPreviousState() const;
	std::string GetCurrentStateName() const;

	void ProcessInput();
	void Update(float deltaTime);
	void ProcessCollisions();
	void Render(Graphics* graphics);

private:
	static GameStateManager* s_instance;
	GameState* m_previousState;
	GameState* m_currentState;
	std::vector<GameState*> m_stateList;
};