#include "FadeTransitionGameState.h"

#include "GameState.h"
#include "GameStateManager.h"
#include "GameStateNameLibrary.h"
#include "LoadingGameState.h"
#include "UIManager.h"
#include "UIView.h"

using namespace GameStateNameLibrary;

FadeTransitionGameState::FadeTransitionGameState() :
	GameState(FadeTransition)
{
}

FadeTransitionGameState::FadeTransitionGameState(GameStateManager* gameStateManager) : FadeTransitionGameState()
{
	m_gameStateManager = gameStateManager;
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

void FadeTransitionGameState::Render(Graphics* graphics)
{
	UIManager::Render(graphics);
}

void FadeTransitionGameState::OnExit()
{
	UIManager::FadeIn();
}