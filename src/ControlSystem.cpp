#include "ControlSystem.h"

#include "UIComboCounterView.h"
#include "UIManager.h"
#include "UIView.h"

ControlSystem::ControlSystem() :
	m_controlsDown(Controls::None),
	m_lastControlsPressed(Controls::None),
	m_inputTimer(0.0f),
	m_comboTimer(0.0f),
	m_doubleTapTimer(0.0f),
	m_canAttack(true),
	m_canCombo(true),
	m_canRun(false),
	m_comboCounter(0),
	m_hitComboCounter(0),
	m_hitComboTimer(0.0f)
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

void ControlSystem::IncrementHitComboCount()
{
	m_hitComboCounter++;
	m_hitComboTimer = 0.0f;

	if(m_hitComboCounter < MinHitComboCount) return;

	UIComboCounterView* comboCounterView = static_cast<UIComboCounterView*>(UIManager::GetView("Combo Counter View"));
	if(comboCounterView) comboCounterView->SetCombo(m_hitComboCounter);
}

void ControlSystem::IncrementComboCount()
{
	m_comboCounter++;

	if(m_comboCounter > MaxCombo) 
		m_comboCounter = 0;
}

void ControlSystem::ResetComboCount()
{
	m_comboCounter = 0;	
}

void ControlSystem::Reset()
{
	m_inputTimer = 0.0f;
	m_comboTimer = 0.0f;
	m_hitComboTimer = 0.0f;
	m_canCombo = false;
	m_lastControlsPressed = Controls::None;
	m_comboCounter = 0;
	m_hitComboCounter = 0;

	CloseHitComboView();
}

void ControlSystem::CloseHitComboView()
{
	UIView* comboCounterView = UIManager::GetView("Combo Counter View");
	if(comboCounterView) comboCounterView->TransitionOut(true);
}

void ControlSystem::Update(float deltaTime)
{
	m_inputTimer += deltaTime;
	m_comboTimer += deltaTime;
	m_doubleTapTimer += deltaTime;
	m_hitComboTimer += deltaTime;

	if(m_comboTimer > ComboResetTime)
	{
		m_canCombo = false;
		m_comboTimer = 0.0f;
		m_comboCounter = 0;
	}

	if(m_hitComboTimer > HitComboWindowDuration && m_hitComboCounter > MinHitComboCount)
	{
		m_hitComboCounter = 0;
		CloseHitComboView();
	}
}
