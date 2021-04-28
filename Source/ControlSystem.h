#pragma once

const unsigned int MaxCombo = 4;
const float ComboTimeLimit = 1.5f; // time given to allow combos again
const float InputTimeLimit = 0.15f; // time given to link combos

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
	MaxControls
};

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