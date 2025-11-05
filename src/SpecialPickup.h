#pragma once

#include "Pickup.h"

class Player;

class SpecialPickup : public Pickup
{
public:
	SpecialPickup();
	~SpecialPickup() {};

	void ApplyEffect(Player* player) override;
};