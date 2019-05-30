#include "EnemyOwnedStates.h"
#include "Enemy.h"
#include "Player.h"
#include "UnitVectors.h"
#include "SpriteSheet.h"
#include "Animator.h"

EnemyGlobalState* EnemyGlobalState::Instance()
{
	static EnemyGlobalState instance;
	return &instance;
}

void EnemyGlobalState::OnEnter(Enemy* enemy)
{

}

void EnemyGlobalState::Execute(Enemy* enemy)
{
}

void EnemyGlobalState::OnExit(Enemy* enemy)
{
}