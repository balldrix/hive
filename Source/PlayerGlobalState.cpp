#include "PlayerOwnedStates.h"
#include "Player.h"
#include "UnitVectors.h"
#include "ControlSystem.h"
#include "SpriteSheet.h"
#include "Animator.h"

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
	// check for keypress
	Controls lastPressed;
	lastPressed = player->GetControlSystem()->GetLastPressed();

	switch(lastPressed)
	{
	case None:
		player->Move(Vector2::Zero);
		break;
	case UpLeft:
		player->Move(UnitVectors::UpLeft);
		//player->FlipHorizontally(true);
		break;
	case Up:
		player->Move(UnitVectors::Up);
		break;
	case UpRight:
		player->Move(UnitVectors::UpRight);
		//player->FlipHorizontally(false);
		break;
	case Right:
		player->Move(UnitVectors::Right);
		//player->FlipHorizontally(false);
		break;
	case DownRight:
		player->Move(UnitVectors::DownRight);
		//player->FlipHorizontally(false);
		break;
	case Down:
		player->Move(UnitVectors::Down);
		break;
	case DownLeft:
		player->Move(UnitVectors::DownLeft);
		//player->FlipHorizontally(true);
		break;
	case Left:
		player->Move(UnitVectors::Left);
		//player->FlipHorizontally(true);
		break;
	case Punch:
		player->Punch();
		break;
	default:
		break;
	}

}

void PlayerGlobalState::OnExit(Player* player)
{
}