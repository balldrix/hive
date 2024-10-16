#pragma once

#include <vector>
#include <string>

class Graphics;

class UIView
{
public:
	enum class ViewStates
	{
		NotVisible,
		AnimatingIn,
		Visible,
		AnimatingOut
	};

	UIView();
	virtual ~UIView() {};

	virtual void Init(std::string name) = 0;
	virtual void Update(float deltaTime) {};
	virtual void Render(Graphics* graphics) = 0;
	
	virtual void TransitionIn(bool isAnimated) { m_isActive = true; };
	virtual void TransitionOut(bool isAnimated) { m_isActive = false; };

	void SetActive(bool isActive);

	void AssignState(std::string stateName);
	bool IsActive() const { return m_isActive; }
	bool IsAnimating() const { return m_isAnimating; }
	std::string GetName() const { return m_name; }
	ViewStates GetCurrentUIViewState() const {	return m_currentViewState;	}

	std::vector<std::string> GetAssignedStates() const { return m_assignedStates; }

	virtual void Shutdown() = 0;	

protected:
	std::string m_name;
	std::vector<std::string> m_assignedStates;
	bool m_isAnimating;
	bool m_isActive;
	float m_transitionTimer;
	ViewStates m_currentViewState;
};