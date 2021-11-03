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
	if(player->GetStateMachine()->GetCurrentState() != PlayerKnockbackState::Instance() &&
		player->GetStateMachine()->GetCurrentState() != PlayerDeadState::Instance())
	{
		Controls keyPressed;
		keyPressed = player->GetControlSystem()->GetKeyPressed();

		switch(keyPressed)
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
			
			if(player->GetControlSystem()->GetLastKeyPressed() == Controls::Right &&
				player->GetControlSystem()->CanRun())
				player->Run();
			else
				player->Walk();

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

			if(player->GetControlSystem()->GetLastKeyPressed() == Controls::Left &&
				player->GetControlSystem()->CanRun())
				player->Run();
			else
				player->Walk();

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