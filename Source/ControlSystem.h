// ControlSystem.h
// Christopher Ball 2019
// Manages player input and combos

#ifndef _CONTROL_SYSTEM_H_
#define _CONTROL_SYSTEM_H_

const unsigned int MaxCombo = 4;
const float ComboTimeLimit = 2.0f;
const float InputTimeLimit = 0.5f;

enum Controls
{
	None,
	UpLeft,
	Up,
	UpRight,
	Right,
	DownRight,
	Down,
	DownLeft,
	Left,
	Attack,
	MaxControls
};

// player controls enum
class ControlSystem
{
public:	
	ControlSystem();
	~ControlSystem();

	void Update(float deltaTime);

	void SetInput(Controls input);
	void CanAttack(bool canAttack);

	Controls GetLastPressed();
	int GetComboCounter() const { return m_comboCounter; }

	void IncrementComboCount();
	
	bool CanAttack() const { return m_canAttack; }
	bool CanCombo() const { return m_canCombo; }

	void ResetTimers();

private:
	Controls m_playerInput;

	float m_inputTimer;
	float m_comboTimer;

	bool m_canAttack;
	bool m_canCombo;
	int m_comboCounter;
};

#endif _CONTROLS_H_