// DummyDeadState.h
// Christopher Ball 2019
// enemy state when dead

#ifndef _DUMMY_DEAD_STATE_
#define _DUMMY_DEAD_STATE_

#include "State.h"

class Dummy;

class DummyDeadState : public State<Dummy>
{
public:
	// static instance call
	static DummyDeadState* Instance();

	virtual void OnEnter(Dummy* enemy);
	virtual void Execute(Dummy* enemy);
	virtual void OnExit(Dummy* enemy);

private:
	DummyDeadState() {}
	DummyDeadState(const DummyDeadState&);
	DummyDeadState operator=(DummyDeadState const&);
};

#endif // !_DUMMYENEMY_DEAD_STATE_