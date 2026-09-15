#include "WasteBossShockwaveState.h"

#include "Enemy.h"
#include "WasteBossIdleState.h"

#include <directxtk/SimpleMath.h>
#include <string>

WasteBossShockwaveState* WasteBossShockwaveState::Instance()
{
	static WasteBossShockwaveState instance("shock-wave");
	return &instance;
}

void WasteBossShockwaveState::OnEnter(Enemy* boss)
{
	boss->GetAnimator()->Reset();
	boss->GetAnimator()->SetAnimation(m_name);
	boss->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	boss->SetTargetVelocity(Vector2::Zero);
}

void WasteBossShockwaveState::Execute(Enemy* boss)
{
	if(!boss->GetAnimator()->IsDone()) return;

	boss->GetStateMachine()->ChangeState(WasteBossIdleState::Instance());
}

void WasteBossShockwaveState::OnExit(Enemy* boss)
{
}

WasteBossShockwaveState::WasteBossShockwaveState(const std::string& name)
{
	m_name = name;
}