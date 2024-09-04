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

void ControlSystem::SetControlsPressed(const Controls& controls)
{
	m_lastControlsPressed = controls;
}

void ControlSystem::SetCanAttack(bool canAttack)
{
	m_canAttack = canAttack;
}

void ControlSystem::ResetInputTimer()
{
	m_inputTimer = 0;
}

void ControlSystem::ResetComboTimer()
{
	m_comboTimer = 0;
}

void ControlSystem::ResetDoubleTap()
{
	if(m_doubleTapTimer < DoubleTapWindowDuration)
	{
		m_canRun = true;
	}
	else
	{
		m_canRun = false;
	}

	m_doubleTapTimer = 0.0f;
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
	m_canCombo = false;
	m_lastControlsPressed = Controls::None;
	m_comboCounter = 0;
}

void ControlSystem::Update(float deltaTime)
{
	m_inputTimer += deltaTime;
	m_comboTimer += deltaTime;
	m_doubleTapTimer += deltaTime;

	if(m_comboTimer > ComboResetTime)
	{
		m_canCombo = false;
		m_comboTimer = 0.0f;
		m_comboCounter = 0;
	}
}
