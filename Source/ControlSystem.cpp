#include "ControlSystem.h"
#include "Timer.h"

ControlSystem::ControlSystem() :
	m_controlsDown(Controls::None),
	m_lastControlsPressed(Controls::None),
	m_inputTimer(0.0f),
	m_comboTimer(0.0f),
	m_doubleTapTimer(0.0f),
	m_canAttack(true),
	m_canCombo(true),
	m_canRun(false),
	m_comboCounter(0)
{
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::SetControlsDown(const Controls& input)
{
	m_controlsDown = input;
}

void ControlSystem::SetControlsPressed(const Controls& controls)
{
	m_lastControlsPressed = controls;
	m_canRun = false;

	if(m_doubleTapTimer < InputTimeLimit)
		m_canRun = true;

	m_doubleTapTimer = 0.0f;
}

void ControlSystem::CanAttack(bool canAttack)
{
	m_canAttack = canAttack;
}

void ControlSystem::IncrementComboCount()
{
	m_comboCounter++;

	if(m_comboCounter > MaxCombo - 1)
	{
		m_comboCounter = 0;
	}
}

void ControlSystem::Reset()
{
	m_inputTimer = 0.0f;
	m_comboTimer = 0.0f;
	m_canCombo = true;
	m_lastControlsPressed = Controls::None;
}

void ControlSystem::Update(float deltaTime)
{
	m_inputTimer += deltaTime;
	m_comboTimer += deltaTime;
	m_doubleTapTimer += deltaTime;

	if(m_inputTimer > InputTimeLimit)
	{
		m_canCombo = false;
		m_comboCounter = 0;
		m_lastControlsPressed = Controls::None;
	}

	if(m_comboTimer > ComboTimeLimit)
	{
		m_canCombo = true;
		m_comboTimer = 0.0f;
	}
}
