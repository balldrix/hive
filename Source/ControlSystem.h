// ControlSystem.h
// Christopher Ball 2018
// Manages player input and combos

#ifndef _CONTROL_SYSTEM_H_
#define _CONTROL_SYSTEM_H_

const unsigned int MaxCombo = 5;
const float ComboTimeLimit = 4.0f;
const float InputTimeLimit = 0.2f;

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


private:
	int m_playerInput[MaxCombo];
	int m_inputIndex;

	float m_inputTimer;
	float m_comboTimer;
};

#endif _CONTROLS_H_