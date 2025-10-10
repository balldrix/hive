#pragma once

#include "IEvent.h"
#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

class Enemy;

class MoveNPCEvent : public IEvent
{
public:
	MoveNPCEvent(Enemy* enemy);
	~MoveNPCEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;
	void OnComplete() override;

private:
	Enemy* m_enemy;
	Vector2 m_destination;
};