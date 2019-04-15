// DummyIdleState.h
// Christopher Ball 2019
// enemy state when Idle

#ifndef _DUMMY_IDLE_STATE_
#define	_DUMMY_IDLE_STATE_

#include "State.h"

// forward declaration
class Dummy;

class DummyIdleState : public State<Dummy>
{
public:
	// static instance call
	static DummyIdleState* Instance();

	virtual void OnEnter(Dummy* enemy);
	virtual void Execute(Dummy* enemy);
	virtual void OnExit(Dummy* enemy);

private:
	DummyIdleState() {}
	DummyIdleState(const DummyIdleState&);
	DummyIdleState operator=(DummyIdleState const&);
};

#endif // !_DUMMY_IDLE_STATE_