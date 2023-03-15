#pragma once

#include "GameObject.h"

class Spritesheet;
class Animator;

class ImpactFx : GameObject
{
public:
	ImpactFx();
	~ImpactFx();

	void Init(Spritesheet* spritesheet, Animator* animator);

private:

	virtual void Render(Graphics* graphics) override;
	virtual void Reset() override;
};