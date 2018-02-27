#include "PlayerIdleState.h"
#include "Player.h"

PlayerIdleState* PlayerIdleState::Instance()
{
	static PlayerIdleState instance;
	return &instance;
}

void PlayerIdleState::OnEnter(Player* player)
{

}

void PlayerIdleState::Execute(Player* player)
{
}

void PlayerIdleState::OnExit(Player* player)
{
}
