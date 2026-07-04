#include "WasteBossIdleState.h"

#include "Enemy.h"
#include "GameplayConstants.h"
#include "WasteBossApproachState.h"

#include <cmath>
#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;
using namespace GameplayConstants;

WasteBossIdleState* WasteBossIdleState::Instance()
{
	static WasteBossIdleState instance("idle");
	return &instance;
}

void WasteBossIdleState::OnEnter(Enemy* boss)
{
	boss->GetAnimator()->Reset();
	boss->GetAnimator()->SetAnimation(m_name);
	boss->GetHitBoxManager()->SetCollidersUsingTag(m_name);

	if(!boss->IsRangedEnemy())
	{
		boss->ResetStateChangeTimer();
	}

	boss->SetTargetVelocity(Vector2::Zero);
}

void WasteBossIdleState::Execute(Enemy* boss)
{
	if(boss->GetHealth() < 1 || boss->GetPlayerTarget()->GetHealth() < 1) return;

	auto verticalDistance = fabs(boss->GetPositionY() - boss->GetPlayerTarget()->GetPositionY());
	auto distance = (boss->GetPosition() - boss->GetPlayerTarget()->GetPosition()).Length();

	if(distance > boss->GetData().attackRange)
	{
		boss->GetStateMachine()->ChangeState(WasteBossApproachState::Instance());
		return;
	}

	if(verticalDistance > VerticalHitRange)
	{
		boss->GetStateMachine()->ChangeState(WasteBossApproachState::Instance());
		return;
	}

	boss->Stop();

	if(boss->GetTimer() > 0)
	{
		return;
	}

	boss->ResetStateChangeTimer();

	if(distance <= boss->GetData().attackRange)
	{
		boss->Attack();
		return;
	}
}

void WasteBossIdleState::OnExit(Enemy* boss)
{
}

WasteBossIdleState::WasteBossIdleState(const std::string& name)
{
	m_name = name;
}
