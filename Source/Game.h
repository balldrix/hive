#pragma once

#include "pch.h"
#include "Timer.h"

class Window;
class Graphics;
class Input;
class GameStateManager;

class Game
{
public:
	Game() noexcept;
	~Game() = default;

	Game(Game&&) = default;
	Game& operator= (Game&&) = default;

	Game(Game const&) = delete;
	Game& operator= (Game const&) = delete;

	void Init(Window* window, Graphics* graphics);

	void Run();

	void ProcessInput();
	void Update(float deltaTime);
	void ProcessCollisions();
	void Render();

	void ReleaseAll();
	void DeleteAll();

	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	LRESULT MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	Window* m_window;
	Graphics* m_graphics;
	SpriteBatch* m_spriteBatch;
	Input* m_input;
	GameStateManager* m_gameStateManager;

	Timer m_timer;
	float m_timerFreq;
	float m_gameTime;
	float m_currentTime;
	float m_clientWidth;
	float m_clientHeight;
	bool m_paused;
	bool m_retryAudio;
};
