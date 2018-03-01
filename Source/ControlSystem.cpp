#include "ControlSystem.h"

ControlSystem::ControlSystem() :
	m_inputIndex(0),
	m_inputTimer(0.0f),
	m_comboTimer(0.0f)
{
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::Init()
{
	for(size_t i = 0; i < MaxCombo; i++)
	{
		m_playerInput[0] = Controls::None;
	}

	m_inputIndex = 0;
	m_inputTimer = 0.0f;
	m_comboTimer = 0.0f;
}

void ControlSystem::SetInput(Controls input)
{
	m_playerInput[m_inputIndex] = input;
}

Controls ControlSystem::GetLastPressed() const
{
	if(m_inputIndex == 0)
	{
		return m_playerInput[MaxCombo - 1];
	}
	else
	{
		return m_playerInput[m_inputIndex];
	}
}

void ControlSystem::Update(float deltaTime)
{
	m_inputTimer += deltaTime;
	m_comboTimer += deltaTime;

	if(m_inputTimer > InputTimeLimit)
	{
		m_inputTimer = 0.0f;
		m_inputIndex++;

		if(m_inputIndex == MaxCombo)
		{
			m_inputIndex = 0;
		}
	}

	if(m_comboTimer > ComboTimeLimit)
	{
		Init();
	}
}
