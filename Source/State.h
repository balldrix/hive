// State.h
// Christopher Ball 2018.
// state template class for use in
// finite state machines

#ifndef _STATE_H_
#define	_STATE_H_

template <typename T>
class State
{
public:
	virtual ~State() {}

	// on enter
	virtual void OnEnter(T*) = 0;

	// state updates
	virtual void Execute(T*) = 0;

	// on exit
	virtual void OnExit(T*) = 0;

};

#endif // !_STATE_H_
