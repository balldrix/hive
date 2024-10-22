#pragma once

#include "pch.h"

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
	virtual void SetPosition(const Vector2& position) {};
	virtual void SetColour(Color colour) {};

	void AssignState(std::string stateName);
	bool IsActive() const { return m_isActive; }
	bool IsAnimating() const { return m_isAnimating; }

	std::string GetName() const { return m_name; }
	ViewStates GetCurrentUIViewState() const {	return m_currentViewState;	}
	std::vector<std::string> GetAssignedStates() const { return m_assignedStates; }
	virtual int GetHeight() { return 0; };
	virtual int GetWidth() { return 0; };
	virtual Color GetColour() { return Colors::White.v; }
	virtual void Shutdown() = 0;	

protected:
	virtual void DoTransition(float deltaTime) {};

	std::string m_name;
	std::vector<std::string> m_assignedStates;
	bool m_isAnimating;
	bool m_isActive;
	float m_transitionTimer;
	ViewStates m_currentViewState;
};