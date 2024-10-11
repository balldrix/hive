#pragma once

#include <vector>
#include <string>

class Graphics;

class UIView
{
public:
	UIView();
	virtual ~UIView() {};

	virtual void Init() = 0;
	virtual void Update(float deltaTime) {};
	virtual void Render(Graphics* graphics) = 0;
	
	virtual void TransitionIn(bool isAnimated) {};
	virtual void TransitionOut(bool isAnimated) {};

	void SetActive(bool isActive);

	void AssignState(std::string stateName);
	bool IsActive() const { return m_isActive; }
	bool IsAnimating() const { return m_isAnimating; }

	virtual void Shutdown() = 0;

protected:
	std::vector<std::string> m_assignedStates;
	bool m_isAnimating;
	bool m_isActive;
	float m_transitionTimer;
};