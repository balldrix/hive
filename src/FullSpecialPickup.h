#pragma once

#include "Pickup.h"

class Player;

class FullSpecialPickup : public Pickup
{
public:
	FullSpecialPickup();
	~FullSpecialPickup() {};

	void ApplyEffect(Player* player) override;
};