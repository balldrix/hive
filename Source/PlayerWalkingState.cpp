#include "PlayerOwnedStates.h"
#include "Player.h"
#include "ControlSystem.h"
#include "UnitVectors.h"

PlayerWalkingState* PlayerWalkingState::Instance()
{
	static PlayerWalkingState instance;
	return &instance;
}

void PlayerWalkingState::OnEnter(Player* player)
{

}

void PlayerWalkingState::Execute(Player* player)
{
	// check for keypress
	Controls lastPressed;
	lastPressed = player->GetControlSystem()->GetLastPressed();

	switch(lastPressed)
	{
	case None:
		player->SetTargetVelocity(Vector2::Zero);
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

	if(player->GetCurrentVelocity() == Vector2::Zero)
	{
		player->SetPlayerState(PlayerIdleState::Instance());
	}
}

void PlayerWalkingState::OnExit(Player* player)
{
}
