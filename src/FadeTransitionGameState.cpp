#include "FadeTransitionGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "LoadingGameState.h"
#include "UIManager.h"
#include "UIView.h"

using namespace GameStateNameLibrary;

FadeTransitionGameState::FadeTransitionGameState() :
	m_graphics(nullptr),
	GameState(FadeTransition)
{
}

FadeTransitionGameState::FadeTransitionGameState(GameStateManager* gameStateManager) : FadeTransitionGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
}

void FadeTransitionGameState::OnEntry()
{
	UIManager::FadeOut();
}

void FadeTransitionGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);

	if(UIManager::IsFading() || UIManager::AnyViewsInState(UIView::ViewStates::AnimatingOut)) return;

	m_gameStateManager->SwitchState(LoadingGameState::GetTargetGameState()->GetStateName());
}

void FadeTransitionGameState::Render()
{
	UIManager::Render(m_graphics);
}

void FadeTransitionGameState::OnExit()
{
	UIManager::FadeIn();
}