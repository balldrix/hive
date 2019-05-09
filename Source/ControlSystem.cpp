#include "ControlSystem.h"

ControlSystem::ControlSystem() :
	m_inputTimer(0.0f),
	m_comboTimer(0.0f),
	m_playerInput(),
	m_canAttack(true),
	m_canCombo(true),
	m_comboCounter(0)
{
}

ControlSystem::~ControlSystem()
{
}


void ControlSystem::SetInput(Controls input)
{
	m_playerInput = input;
}

void ControlSystem::CanAttack(bool canAttack)
{
	m_canAttack = canAttack;
}

Controls ControlSystem::GetLastPressed()
{
	return m_playerInput;
}

void ControlSystem::IncrementComboCount()
{
	m_comboCounter = (m_comboCounter + 1) % MaxCombo;
}

void ControlSystem::ResetTimers()
{
	m_inputTimer = 0.0f;
	m_comboTimer = 0.0f;
	m_canCombo = true;
}

void ControlSystem::Update(float deltaTime)
{
	m_inputTimer += deltaTime;
	m_comboTimer += deltaTime;

	if(m_inputTimer > InputTimeLimit)
	{
		m_canCombo = false;
		m_comboCounter = 0;
	}

	if(m_comboTimer > ComboTimeLimit)
	{
		m_canCombo = true;
	}
}
