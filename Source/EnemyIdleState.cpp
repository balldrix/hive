#include "EnemyIdleState.h"


EnemyIdleState* EnemyIdleState::Instance()
{
	static EnemyIdleState instance("Idle");
	return &instance;
}

void EnemyIdleState::OnEnter(Enemy* enemy)
{
}

void EnemyIdleState::Execute(Enemy* enemy)
{
}

void EnemyIdleState::OnExit(Enemy* enemy)
{
}

EnemyIdleState::EnemyIdleState(std::string name)
{

}