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
	if(m_currentState != nullptr)
	{
		m_currentState->OnExit();
	}

	if(!m_stateList.empty())
	{
		for(unsigned int i = 0; i < m_stateList.size(); i++)
		{
			delete m_stateList[i];
		}
		m_stateList.clear();
	}
}

void GameStateManager::Init(Graphics* graphics, Input* input)
{
	m_graphics = graphics;
	m_input = input;
}

void GameStateManager::AddState(GameState* state)
{
	m_stateList.push_back(state);
}

void GameStateManager::SwitchState(std::string stateName)
{
	std::string currentStateName = "none";
	if (m_currentState != nullptr) currentStateName = m_currentState->GetStateName();
	std::string message = fmt::format("Switching State from {0} to {1} game state", currentStateName, stateName);
	Logger::LogInfo(message);

	if(m_currentState != nullptr)
	{
		m_currentState->OnExit();
		m_currentState = nullptr;
	}

	for(unsigned int i = 0; i < m_stateList.size(); i++)
	{
		if(m_stateList[i]->GetStateName() == stateName)
		{
			m_currentState = m_stateList[i];
			m_currentState->OnEntry();
			return;
		}
	}

	std::string error = " Error finding game state in SwitchState method GameStateManager.cpp line 60; \n"; // error message
	Error::FileLog(error);
	MessageBox(m_graphics->GetHwnd(), L"Error loading GameState. See Logs/Error.txt", L"Error!", MB_OK);
	PostQuitMessage(0);
}

GameState* GameStateManager::GetCurrentState() const
{
	return m_currentState;
}

std::string GameStateManager::GetCurrentStateName() const
{
	if(m_currentState != nullptr)
	{
		return m_currentState->GetStateName();
	}
	return "";
}

void GameStateManager::ProcessInput()
{
	if(m_currentState != nullptr)
	{
		m_currentState->ProcessInput();
	}
}

void GameStateManager::Update(float deltaTime)
{
	if(m_currentState != nullptr)
	{
		m_currentState->Update(deltaTime);
	}
}

void GameStateManager::ProcessCollisions()
{
	if(m_currentState != nullptr)
	{
		m_currentState->ProcessCollisions();
	}
}

void GameStateManager::Render()
{
	if(m_currentState != nullptr)
	{
		m_currentState->Render();
	}
}

void GameStateManager::ReleaseAll()
{
	if(m_currentState != nullptr)
	{
		m_currentState->ReleaseAll();
	}
}