#include "GameStateManager.h"

GameStateManager::GameStateManager() :
m_currentState(NULL)
{
}

GameStateManager::~GameStateManager()
{
	if (m_currentState != NULL)
	{
		m_currentState->OnExit();
	}

	ListNode<GameState*>* node = m_stateList.GetFirst();

	while (node != NULL)
	{
		GameState* state = node->GetData();
		delete state;
		node = node->GetNext();
	}
}

void
GameStateManager::CreateGlobalSystems(HWND hWindow, Graphics* graphics, Input* input)
{
	m_hWindow = hWindow;
	m_pGraphics = graphics;
	m_pInput = input;
}

void
GameStateManager::AddState(GameState* state)
{
	ListNode<GameState*>* node = m_stateList.GetFirst();

	while (node != NULL)
	{
		GameState* currentState = node->GetData();
		if (currentState->GetStateName() == state->GetStateName())
		{
			delete state;
			return;
		}
		node = node->GetNext();
	}

	m_stateList.Insert(state);
}

void
GameStateManager::SwitchState(const char* stateName)
{
	if (m_currentState != NULL)
	{
		m_currentState->OnExit();
		m_currentState = NULL;
	}

	ListNode<GameState*>* node = m_stateList.GetFirst();

	while (node != NULL)
	{
		GameState* state = node->GetData();

		if (state->GetStateName() == stateName)
		{
			m_currentState = state;
			m_currentState->OnEntry();
			return;
		}
		node = node->GetNext();
	}
}

GameState*		
GameStateManager::GetCurrentState() const
{
	return m_currentState;
}

const char*
GameStateManager::GetCurrentStateName() const
{
	if (m_currentState != NULL)
	{
		return m_currentState->GetStateName();
	}
	return "";
}

void	
GameStateManager::Update(float deltaTime)
{
	if (m_currentState != NULL)
	{
		m_currentState->CheckInput(deltaTime);
		m_currentState->Update(deltaTime);
	}
}

void			
GameStateManager::Render()
{
	if (m_currentState != NULL)
	{
		m_currentState->Render();
	}
}

void			
GameStateManager::OnLostDevice()
{
	if (m_currentState != NULL)
	{
		m_currentState->OnLostDevice();
	}
}

void
GameStateManager::ResetAll()
{
	if (m_currentState != NULL)
	{
		m_currentState->ResetAll();
	}
}

void 
GameStateManager::ReleaseAll()
{
	if (m_currentState != NULL)
	{
		m_currentState->ReleaseAll();
	}
}