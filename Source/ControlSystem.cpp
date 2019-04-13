#include "ControlSystem.h"

ControlSystem::ControlSystem() :
	m_inputIndex(0),
	m_inputTimer(0.0f),
	m_comboTimer(0.0f),
	m_playerInput(),
	m_canAttack(true)
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

void ControlSystem::CanAttack(bool canAttack)
{
	m_canAttack = canAttack;
}

Controls ControlSystem::GetLastPressed()
{
	if(m_inputIndex == MaxCombo)
	{
		m_inputIndex = 0;
	}

		int index = m_inputIndex;
		m_inputIndex++;
		return m_playerInput[index];
}

void ControlSystem::Update(float deltaTime)
{
	m_inputTimer += deltaTime;
	m_comboTimer += deltaTime;

	//if(m_inputTimer > InputTimeLimit)
	//{
	//	m_inputTimer = 0.0f;
	//	m_inputIndex++;

	//	if(m_inputIndex == MaxCombo)
	//	{
	//		Init();
	//	}
	//}
}
