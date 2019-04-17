// DummyHurtState.h
// Christopher Ball 2019
// enemy state when hurt

#ifndef _DUMMY_HURT_STATE_
#define _DUMMY_HURT_STATE_

#include "State.h"

class Dummy;

class DummyHurtState : public State<Dummy>
{
public:
	// static instance call
	static DummyHurtState* Instance();

	virtual void OnEnter(Dummy* enemy);
	virtual void Execute(Dummy* enemy);
	virtual void OnExit(Dummy* enemy);

private:
	DummyHurtState() {}
	DummyHurtState(std::string name);
	DummyHurtState(const DummyHurtState&);
	DummyHurtState operator=(DummyHurtState const&);
};

#endif // !_DUMMY_HURT_STATE_