#include "PlayerOwnedStates.h"
#include "Player.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

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
	Controls lastPressed;
	lastPressed = player->GetControlSystem()->GetLastPressed();

	switch(lastPressed)
	{
	case None:
		break;
	case UpLeft:
		player->SetTargetVelocity(UnitVectors::UpLeft);
		break;
	case Up:
		player->SetTargetVelocity(UnitVectors::Up);
		break;
	case UpRight:
		player->SetTargetVelocity(UnitVectors::UpRight);
		break;
	case Right:
		player->SetTargetVelocity(UnitVectors::Right);
		break;
	case DownRight:
		player->SetTargetVelocity(UnitVectors::DownRight);
		break;
	case Down:
		player->SetTargetVelocity(UnitVectors::Down);
		break;
	case DownLeft:
		player->SetTargetVelocity(UnitVectors::DownLeft);
		break;
	case Left:
		player->SetTargetVelocity(UnitVectors::Left);
		break;
	default:
		break;
	}

	if(player->GetCurrentVelocity() != Vector2::Zero)
	{
		player->SetPlayerState(PlayerWalkingState::Instance());
	}
}

void PlayerIdleState::OnExit(Player* player)
{
}
