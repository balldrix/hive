#pragma once

const unsigned int MaxCombo = 4;
const float ComboResetTime = 0.7f;
const float HitComboWindowDuration = 3.0f;
const float DoubleTapWindowDuration = 0.2f;
const int MinHitComboCount = 10;

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
	NormalAttack,
	StrongAttack,
	SpecialAttack,
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
	void ResetInputTimer();
	void ResetComboTimer();
	void ResetDoubleTap();

	Controls GetKeyPressed() const { return m_controlsDown; }
	Controls GetLastKeyPressed() const { return m_lastControlsPressed; }
	int GetComboCounter() const { return m_comboCounter; }

	void IncrementHitComboCount();
	void IncrementComboCount();
	void ResetComboCount();
	
	bool CanAttack() const { return m_canAttack; }
	bool CanCombo() const { return m_canCombo; }
	bool CanRun() const { return m_canRun; }

	void Reset();

private:
	void CloseHitComboView();
	Controls m_controlsDown;
	Controls m_lastControlsPressed;

	float m_inputTimer;
	float m_comboTimer;
	float m_hitComboTimer;
	float m_doubleTapTimer;

	bool m_canAttack;
	bool m_canCombo;
	int m_comboCounter;
	int m_hitComboCounter;
	bool m_canRun;
};