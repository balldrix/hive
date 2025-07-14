#include "GameStateManager.h"

#include "GameState.h"
#include "Graphics.h"
#include "Logger.h"
#include "UIManager.h"

#include <string>

GameStateManager* GameStateManager::s_instance = nullptr;

GameStateManager::GameStateManager() :
	m_previousState(nullptr),
	m_currentState(nullptr),
	m_graphics(nullptr),
	m_input(nullptr)
{
	s_instance = this;
}

GameStateManager::~GameStateManager()
{
	if(!m_stateList.empty())
	{
		for(unsigned int i = 0; i < m_stateList.size(); i++)
		{
			delete m_stateList[i];
		}
		m_stateList.clear();
	}

	s_instance = nullptr;
}

GameStateManager* GameStateManager::Instance()
{
	if(s_instance == nullptr)
	{
		Logger::LogError("No instance of GameStateManager exists");
	}

	return s_instance;
}

void GameStateManager::Init(Window* window, Graphics* graphics, Input* input)
{
	Logger::LogInfo("Initialising Gamestate manager.");

	m_window = window;
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
	std::string message = fmt::format("Switching State from {0} state to {1} state.", currentStateName, stateName);
	Logger::LogInfo(message);

	if(m_currentState != nullptr)
	{
		m_previousState = m_currentState;
		m_currentState->OnExit();
		m_currentState = nullptr;
	}

	for(unsigned int i = 0; i < m_stateList.size(); i++)
	{
		if(m_stateList[i]->GetStateName() == stateName)
		{
			m_currentState = m_stateList[i];
			m_currentState->OnEntry();
			UIManager::OnGameStateChange(stateName);
			return;
		}
	}

	std::string error = fmt::format("Error finding game state {} in SwitchState method GameStateManager.cpp line 60.", stateName);
	Logger::LogError(error);
	MessageBox(m_graphics->GetHwnd(), L"Error loading GameState. See Logs/Log.txt", L"Error!", MB_OK);
	PostQuitMessage(0);
}

void GameStateManager::ProceedToPreviousState()
{
	SwitchState(m_previousState->GetStateName());
}

GameState* GameStateManager::GetState(std::string stateName) const
{
	for(auto it = m_stateList.begin(); it != m_stateList.end(); ++it)
	{
		if ((*it)->GetStateName() == stateName)
			return *it;
	}

	return nullptr;
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