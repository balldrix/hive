#include "FullSpecialPickup.h"

#include "Pickup.h"
#include "Player.h"
#include "PlayerConstants.h"

using namespace PlayerConstants;

FullSpecialPickup::FullSpecialPickup() : Pickup()
{
}

void FullSpecialPickup::ApplyEffect(Player* player)
{
	player->SetSpecial(MaxSpecial);
}
