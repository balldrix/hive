#include "GameStateManager.h"
#include "GameState.h"
#include "Graphics.h"
#include "Error.h"

GameStateManager::GameStateManager() :
m_currentState(nullptr),
m_graphics(nullptr),
m_input(nullptr)
{
}

GameStateManager::~GameStateManager()
{
	// if current game state is 
	if (m_currentState != nullptr)
	{
		m_currentState->OnExit();
	}

	if(!m_stateList.empty())
	{
		// delete all NPC from the list
		for(unsigned int i = 0; i < m_stateList.size(); i++)
		{
			delete m_stateList[i];
		}
		// clear list
		m_stateList.clear();
	}

}

void
GameStateManager::Init(Graphics* graphics, Input* input)
{
	// copy pointers
	m_graphics = graphics;
	m_input = input;
}

void
GameStateManager::AddState(GameState* state)
{
	// push state to vector list
	m_stateList.push_back(state);
}

void
GameStateManager::SwitchState(const wchar_t* stateName)
{
	// if current state contains points to a state
	if (m_currentState != nullptr)
	{
		// call OnExit method and clear pointer
		m_currentState->OnExit(); 
		m_currentState = nullptr;
	}

	// loop through state list
	for(unsigned int i = 0; i < m_stateList.size(); i++)
	{
		if (m_stateList[i]->GetStateName() == stateName)
		{			
			m_currentState = m_stateList[i]; // set current state pointer
			m_currentState->OnEntry(); // call OnEntry method
			return;
		}
	}

	// if this method hasn't returned by now
	// the state name is incorrect
	std::string error = " Error finding game state in SwitchState method GameStateManager.cpp line 60; \n"; // error message
	Error::FileLog(error);
	MessageBox(m_graphics->GetHwnd(), L"Error loading GameState. See Logs/Error.txt", L"Error!", MB_OK); // display loading texture error message
	PostQuitMessage(0); // quit game
}

GameState*		
GameStateManager::GetCurrentState() const
{
	return m_currentState; // return current state
}

const wchar_t*
GameStateManager::GetCurrentStateName() const
{
	if (m_currentState != nullptr)
	{
		return m_currentState->GetStateName(); // return current state name
	}
	return L""; // if no state name exists return ""
}

void
GameStateManager::ProcessInput()
{
	if(m_currentState != nullptr)
	{
		m_currentState->ProcessInput(); // process input for current state
	}
}

void	
GameStateManager::Update(float deltaTime)
{
	if (m_currentState != nullptr)
	{
		m_currentState->Update(deltaTime); // update current state
	}
}

void			
GameStateManager::Render()
{
	if (m_currentState != nullptr)
	{
		m_currentState->Render(); // render current state
	}
}

void 
GameStateManager::ReleaseAll()
{
	if (m_currentState != nullptr)
	{
		m_currentState->ReleaseAll(); // release all resources for currents state
	}
}