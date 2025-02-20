#include "PlayerGlobalState.h"

#include "Player.h"
#include "PlayerDeadState.h"
#include "PlayerKnockbackState.h"

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
	if(player->GetStateMachine()->IsInState(*PlayerKnockbackState::Instance()) ||
		player->GetStateMachine()->IsInState(*PlayerDeadState::Instance()))
	{
		return;
	}

	if(player->GetCurrentVelocity().x < 0)
		player->FlipHorizontally(true);

	if(player->GetCurrentVelocity().x > 0)
		player->FlipHorizontally(false);
}

void PlayerGlobalState::OnExit(Player* player)
{
}