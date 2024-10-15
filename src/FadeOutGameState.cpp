#include "FadeOutGameState.h"

#include "UIManager.h"
#include "GameStateManager.h"
#include "LoadingGameState.h"

FadeOutGameState::FadeOutGameState() :
	GameState("FadeOut")
{
}

FadeOutGameState::FadeOutGameState(GameStateManager* gameStateManager) : FadeOutGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
}

FadeOutGameState::~FadeOutGameState()
{
}

void FadeOutGameState::OnEntry()
{
	UIManager::FadeOut();
}

void FadeOutGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);

	if(UIManager::IsFading()) return;

	//UIManager::OnGameStateChange(LoadingGameState::s_targetGameState->GetStateName());
	//m_gameStateManager->SwitchState("FadeIn");
}

void FadeOutGameState::Render()
{
	UIManager::Render(m_graphics);
}

void FadeOutGameState::OnExit()
{
}
