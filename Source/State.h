// State.h
// Christopher Ball 2019
// state template class for use in
// finite state machines

#ifndef _STATE_H_
#define	_STATE_H_

#include "pch.h"

template <typename T>
class State
{
protected:
	std::string m_name;

public:
	virtual ~State() {}

	// on enter
	virtual void OnEnter(T*) = 0;

	// state updates
	virtual void Execute(T*) = 0;

	// on exit
	virtual void OnExit(T*) = 0;

	// return state name
	std::string GetName() const { return m_name; }
};

#endif // !_STATE_H_
