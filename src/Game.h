#pragma once

#include "Timer.h"

#include <directxtk/SpriteBatch.h>

using namespace DirectX;

class Window;
class Graphics;
class Input;
class GameStateManager;

class Game
{
public:
	Game() noexcept;
	~Game();

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

	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	void Shutdown();

	LRESULT MessageHandler(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	Window* m_window;
	Graphics* m_graphics;
	Input* m_input;
	GameStateManager* m_gameStateManager;

	Timer m_timer;
	unsigned __int64 m_timerFreq;
	float m_gameTime;
	unsigned __int64 m_lastTime;
	float m_clientWidth;
	float m_clientHeight;
	bool m_paused;
	bool m_retryAudio;
};
