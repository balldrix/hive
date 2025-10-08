#pragma once

#include "IEvent.h"
#include "Player.h"

class MovePlayerEvent : public IEvent
{
public:
	MovePlayerEvent(Player* player);
	~MovePlayerEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;
	void OnComplete() override {};
	void Reset() override;
private:
	Player* m_player;
	float m_distance;
};