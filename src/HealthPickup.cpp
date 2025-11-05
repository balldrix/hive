#include "HealthPickup.h"

#include "Pickup.h"
#include "Player.h"

HealthPickup::HealthPickup() : Pickup()
{
}

void HealthPickup::ApplyEffect(Player* player)
{
	const int HealthIncrease = 20;
	player->IncreaseHealth(20);
}