#include "FullHealthPickup.h"

#include "Pickup.h"
#include "Player.h"

FullHealthPickup::FullHealthPickup() : Pickup()
{
}

void FullHealthPickup::ApplyEffect(Player* player)
{
	int maxHealth = player->GetMaxHealth();
	player->SetHealth(maxHealth);
}

void FullHealthPickup::Shutdown()
{
	delete m_spritesheet;
	m_spritesheet = nullptr;
}
