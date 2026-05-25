#include "WasteBossSlamState.h"

#include "Animator.h"
#include "Enemy.h"
#include "HitBoxManager.h"
#include "StateMachine.h"
#include "WasteBossIdleState.h"

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

WasteBossSlamState* WasteBossSlamState::Instance()
{
	static WasteBossSlamState instance("slam");
	return &instance;
}

void WasteBossSlamState::OnEnter(Enemy* boss)
{
	boss->GetAnimator()->Reset();
	boss->GetAnimator()->SetAnimation(m_name);
	boss->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	boss->SetTargetVelocity(Vector2::Zero);

	auto directionToTarget = boss->GetPlayerTarget()->GetPosition().x - boss->GetPositionX();
	boss->FlipHorizontally(directionToTarget < 0);
}

void WasteBossSlamState::Execute(Enemy* boss)
{
	if(boss->GetAnimator()->IsDone())
	{
		boss->GetStateMachine()->ChangeState(WasteBossIdleState::Instance());
	}
}

void WasteBossSlamState::OnExit(Enemy* boss)
{
}

WasteBossSlamState::WasteBossSlamState(const std::string& name)
{
	m_name = name;
}
