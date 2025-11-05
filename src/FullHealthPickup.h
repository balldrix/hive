#pragma once

#include "Pickup.h"

class Player;

class FullHealthPickup : public Pickup
{
public:
	FullHealthPickup();
	~FullHealthPickup() {};

	void ApplyEffect(Player* player) override;
	void Shutdown() override;
};