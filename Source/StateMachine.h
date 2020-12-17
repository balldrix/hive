// StateMachine.h
// Christopher Ball 2019
// manages game object states

#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include "State.h"

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

		// store previous state
		m_previousState = m_currentState;

		// call on exit for current state
		m_currentState->OnExit(m_owner);

		// set new state
		m_currentState = newState;

		// call on entry for new state
		m_currentState->OnEnter(m_owner);
	}

	void RevertToPreviousState()
	{
		ChangeState(m_previousState);
	}

	State<T>* GetCurrentState() const { return m_currentState; }
	State<T>* GetPreviousState() const { return m_previousState; }
	State<T>* GetGlobalState() const { return m_globalState; }

	bool IsInState(const State<T>& state) const
	{
		return typeid(*m_currentState) == typeid(state);
	}

private:
	T* m_owner;						// pointer to owner of state
	State<T>* m_currentState;		// current state to update
	State<T>* m_previousState;		// record of previous state
	State<T>* m_globalState;		// global state for common methods
};

#endif // !_STATEMACHINE_H_
