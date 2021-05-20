#include "GameState.h"

GameState::GameState() :
	m_stateName(L""),
	m_inputTimer(0.0f),
	m_inputReady(false)
{
}

GameState::GameState(const wchar_t* stateName) :
	m_inputTimer(0.0f),
	m_inputReady(false)
{
	m_stateName = stateName;
}

const wchar_t* GameState::GetStateName() const
{
	return m_stateName;
}