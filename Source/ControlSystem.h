// ControlSystem.h
// Christopher Ball 2019
// Manages player input and combos

#ifndef _CONTROL_SYSTEM_H_
#define _CONTROL_SYSTEM_H_

const unsigned int MaxCombo = 5;
const float ComboTimeLimit = 2.0f;
const float InputTimeLimit = 0.05f;

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
	Jab,
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
	Controls GetLastPressed() const;

private:
	Controls m_playerInput[MaxCombo];
	int m_inputIndex;

	float m_inputTimer;
	float m_comboTimer;
};

#endif _CONTROLS_H_