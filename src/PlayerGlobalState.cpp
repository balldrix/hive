#include "PlayerGlobalState.h"

#include "Player.h"

PlayerGlobalState* PlayerGlobalState::Instance()
{
	static PlayerGlobalState instance;
	return &instance;
}

void PlayerGlobalState::OnEnter(Player* player)
{
}

void PlayerGlobalState::Execute(Player* player)
{
	if(player->GetCurrentVelocity().x < 0)
		player->FlipHorizontally(true);

	if(player->GetCurrentVelocity().x > 0)
		player->FlipHorizontally(false);
}

void PlayerGlobalState::OnExit(Player* player)
{
}