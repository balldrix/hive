#pragma once

#include "ObjectPool.h"
#include "SpriteFx.h"

class ImpactFxPool : public ObjectPool<SpriteFx>
{
public:
	ImpactFxPool();
	virtual ~ImpactFxPool() {};

	SpriteFx* Get() override;
};