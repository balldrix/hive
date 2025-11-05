#include "SpecialPickup.h"

#include "Pickup.h"
#include "Player.h"

SpecialPickup::SpecialPickup() : Pickup()
{
}

void SpecialPickup::ApplyEffect(Player* player)
{
	const float amount = 30.0f;
	player->IncreaseSpecial(amount);
}
