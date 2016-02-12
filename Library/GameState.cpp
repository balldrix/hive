#include "GameState.h"

GameState::GameState() :
m_inputTimer(0),
m_keyPressed(false)
{

}

GameState::GameState(const char* stateName) :
m_inputTimer(0),
m_keyPressed(false)
{
	m_stateName = stateName;
}

const char*
GameState::GetStateName() const
{
	return m_stateName;
}