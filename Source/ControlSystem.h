#pragma once

const unsigned int MaxCombo = 4;
const float ComboResetTime = 1.5f;
const float ComboWindowDuration = 0.15f;
const float DoubleTapWindowDuration = 0.2f;

enum class Controls
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
	Roll,
	MaxControls
};

class ControlSystem
{
public:	
	ControlSystem();
	~ControlSystem();

	void Update(float deltaTime);

	void SetControlsPressed(const Controls& controls);
	void SetCanAttack(bool canAttack);

	Controls GetKeyPressed() const { return m_controlsDown; }
	Controls GetLastKeyPressed() const { return m_lastControlsPressed; }
	int GetComboCounter() const { return m_comboCounter; }

	void IncrementComboCount();
	
	bool CanAttack() const { return m_canAttack; }
	bool CanCombo() const { return m_canCombo; }
	bool CanRun() const { return m_canRun; }

	void Reset();

private:
	Controls m_controlsDown;
	Controls m_lastControlsPressed;

	float m_inputTimer;
	float m_comboTimer;
	float m_doubleTapTimer;

	bool m_canAttack;
	bool m_canCombo;
	int m_comboCounter;
	bool m_canRun;
};