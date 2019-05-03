// ControlSystem.h
// Christopher Ball 2019
// Manages player input and combos

#ifndef _CONTROL_SYSTEM_H_
#define _CONTROL_SYSTEM_H_

const unsigned int MaxCombo = 99;
const float InputTimeLimit = 0.008f;

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

	void Init();
	void Update(float deltaTime);
	void SetInput(Controls input);
	void CanAttack(bool canAttack);
	Controls GetLastPressed();
	bool CanAttack() const { return m_canAttack; }

private:
	Controls m_playerInput[MaxCombo];
	int m_inputIndex;

	float m_inputTimer;
	float m_comboTimer;

	bool m_canAttack;
};

#endif _CONTROLS_H_