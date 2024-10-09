#include "GameState.h"
#include "string.h"

GameState::GameState() :
	m_gameStateManager(nullptr),
	m_stateName(""),
	m_inputTimer(0.0f),
	m_inputReady(false)
{
}

GameState::GameState(std::string stateName) :
	m_gameStateManager(nullptr),
	m_inputTimer(0.0f),
	m_inputReady(false),
	m_stateName(stateName)
{
}

std::string GameState::GetStateName() const
{
	return m_stateName;
}