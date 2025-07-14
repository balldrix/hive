#pragma once

#include <string>
#include <vector>

class Window;
class Graphics;
class Input;
class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	static GameStateManager* Instance();

	void Init(Window* window, Graphics* graphics, Input* input);

	void AddState(GameState* state);
	void SwitchState(std::string stateName);
	void ProceedToPreviousState();

	GameState* GetState(std::string stateName) const;
	GameState* GetCurrentState() const;
	std::string GetCurrentStateName() const;

	void ProcessInput();
	void Update(float deltaTime);
	void ProcessCollisions();
	void Render();

	Window* GetWindow() const { return m_window; }
	Graphics* GetGraphics() const { return m_graphics; }
	Input* GetInput() const { return m_input; }

private:
	static GameStateManager* s_instance;
	GameState* m_previousState;
	GameState* m_currentState;
	std::vector<GameState*> m_stateList;

	Window* m_window;
	Graphics* m_graphics;
	Input* m_input;
};