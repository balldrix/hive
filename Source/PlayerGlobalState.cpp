#include "PlayerOwnedStates.h"
#include "StateMachine.h"
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
	// true if the player is not knocked back or dead
	if(player->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
		player->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance())
	{

		// check for keypress
		Controls lastPressed;
		lastPressed = player->GetControlSystem()->GetLastPressed();

		switch(lastPressed)
		{
		case Controls::None:
			player->Move(Vector2::Zero);
			break;
		case Controls::UpLeft:
			player->Move(UnitVectors::UpLeft);
			break;
		case Controls::Up:
			player->Move(UnitVectors::Up);
			break;
		case Controls::UpRight:
			player->Move(UnitVectors::UpRight);
			break;
		case Controls::Right:
			player->Move(UnitVectors::Right);
			break;
		case Controls::DownRight:
			player->Move(UnitVectors::DownRight);
			break;
		case Controls::Down:
			player->Move(UnitVectors::Down);
			break;
		case Controls::DownLeft:
			player->Move(UnitVectors::DownLeft);
			break;
		case Controls::Left:
			player->Move(UnitVectors::Left);
			break;
		case Controls::Attack:
			player->Attack();
			break;
		default:
			break;
		}

		if(player->GetCurrentVelocity().x < 0)
			player->FlipHorizontally(true);

		if(player->GetCurrentVelocity().x > 0)
			player->FlipHorizontally(false);
	}
}


void PlayerGlobalState::OnExit(Player* player)
{
}