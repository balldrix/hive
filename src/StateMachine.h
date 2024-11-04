#pragma once

#include "State.h"

#include <cassert>

template <class T>
class StateMachine
{
public:
	StateMachine() :
		m_owner(nullptr),
		m_currentState(nullptr),
		m_previousState(nullptr),
		m_globalState(nullptr)
	{}

	StateMachine(T* owner) :
		m_owner(owner),
		m_currentState(nullptr),
		m_previousState(nullptr),
		m_globalState(nullptr)
	{}

	virtual ~StateMachine() {}

	void Init(State<T>* currentState, State<T>* previousState, State<T>* globalState)
	{
		m_currentState = currentState;
		m_previousState = previousState;
		m_globalState = globalState;
	}

	void Update() const
	{
		if(m_globalState) 
		{
			m_globalState->Execute(m_owner);
		}

		if(m_currentState)
		{
			m_currentState->Execute(m_owner);
		}
	}

	void ChangeState(State<T>* newState)
	{
		assert(m_currentState && newState);
		m_previousState = m_currentState;
		m_currentState->OnExit(m_owner);
		m_currentState = newState;
		m_currentState->OnEnter(m_owner);
	}

	void RevertToPreviousState() { ChangeState(m_previousState); }

	State<T>* GetCurrentState() const { return m_currentState; }
	State<T>* GetPreviousState() const { return m_previousState; }
	State<T>* GetGlobalState() const { return m_globalState; }

	bool IsInState(const State<T>& state) const { return typeid(*m_currentState) == typeid(state); }

private:
	T* m_owner;				
	State<T>* m_currentState;
	State<T>* m_previousState;
	State<T>* m_globalState;
};