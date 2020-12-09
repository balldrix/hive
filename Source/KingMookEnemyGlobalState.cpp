#include "KingMookEnemyGlobalState.h"

KingMookEnemyGlobalState* KingMookEnemyGlobalState::Instance()
{
	static KingMookEnemyGlobalState instance;
	return &instance;
}

void KingMookEnemyGlobalState::OnEnter(Enemy* owner)
{
}

void KingMookEnemyGlobalState::Execute(Enemy* owner)
{
}

void KingMookEnemyGlobalState::OnExit(Enemy* owner)
{
}