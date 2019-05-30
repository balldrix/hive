// DummyKnockbackState.h
// Christopher Ball 2019
// enemy state when knocked back

#ifndef _DUMMY_KNOCKBACK_STATE_
#define _DUMMY_KNOCKBACK_STATE_

#include "State.h"

class Dummy;

class DummyKnockbackState : public State<Dummy>
{
public:
	// static instance call
	static DummyKnockbackState* Instance();

	virtual void OnEnter(Dummy* enemy);
	virtual void Execute(Dummy* enemy);
	virtual void OnExit(Dummy* enemy);

private:
	DummyKnockbackState() {}
	~DummyKnockbackState() {}
	DummyKnockbackState(std::string name);
	DummyKnockbackState(const DummyKnockbackState&);
	DummyKnockbackState& operator=(const DummyKnockbackState&);
};

#endif // !_DUMMY_KNOCKBACK_STATE_