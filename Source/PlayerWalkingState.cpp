#include "PlayerOwnedStates.h"
#include "Player.h"
#include "ControlSystem.h"
#include "Sprite.h"
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
		player->GetSprite()->SetFlipEffect(SpriteEffects::SpriteEffects_FlipHorizontally);
		break;
	case Up:
		player->SetTargetVelocity(UnitVectors::Up);
		break;
	case UpRight:
		player->SetTargetVelocity(UnitVectors::UpRight);
		player->GetSprite()->SetFlipEffect(SpriteEffects::SpriteEffects_None);
		break;
	case Right:
		player->SetTargetVelocity(UnitVectors::Right);
		player->GetSprite()->SetFlipEffect(SpriteEffects::SpriteEffects_None);
		break;
	case DownRight:
		player->SetTargetVelocity(UnitVectors::DownRight);
		player->GetSprite()->SetFlipEffect(SpriteEffects::SpriteEffects_None);
		break;
	case Down:
		player->SetTargetVelocity(UnitVectors::Down);
		break;
	case DownLeft:
		player->SetTargetVelocity(UnitVectors::DownLeft);
		player->GetSprite()->SetFlipEffect(SpriteEffects::SpriteEffects_FlipHorizontally);
		break;
	case Left:
		player->SetTargetVelocity(UnitVectors::Left);
		player->GetSprite()->SetFlipEffect(SpriteEffects::SpriteEffects_FlipHorizontally);
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
