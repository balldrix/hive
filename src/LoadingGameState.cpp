#include "LoadingGameState.h"

#include "GameStateManager.h"
#include "Graphics.h"
#include "UIManager.h"

GameState* LoadingGameState::s_targetGameState;

LoadingGameState::LoadingGameState() :
	m_graphics(nullptr),
	GameState("Loading")
{
}

LoadingGameState::LoadingGameState(GameStateManager* gameStateManager) : LoadingGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = gameStateManager->GetGraphics();
}

LoadingGameState::~LoadingGameState()
{
	OnExit();
}

void LoadingGameState::Update(float deltaTime)
{
	static float timer = 3.0f;
	timer -= deltaTime;

	if (timer <= 0.0f)
		m_gameStateManager->SwitchState("FadeOut");

	UIManager::Update(deltaTime);
}

void LoadingGameState::Render()
{
	UIManager::Render(m_graphics);
}