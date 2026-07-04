#include "WasteBossSlamState.h"

#include "Animator.h"
#include "ControlSystem.h"
#include "Enemy.h"
#include "HitBoxManager.h"
#include "Player.h"
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

	auto player = boss->GetPlayerTarget();
	player->GetSprite()->DisableSprite();
	player->SetInputEnabled(false);
	player->Stop();
	player->GetControlSystem()->SetControlsPressed(Controls::None);
}

void WasteBossSlamState::Execute(Enemy* boss)
{
	if(boss->GetAnimator()->IsDone())
	{
		boss->GetPlayerTarget()->ApplyDamage(boss, boss->GetDamageData().amount);
		boss->GetStateMachine()->ChangeState(WasteBossIdleState::Instance());
	}
}

void WasteBossSlamState::OnExit(Enemy* boss)
{
	auto player = boss->GetPlayerTarget();
	player->GetSprite()->EnableSprite();
	player->SetInputEnabled(true);
}

WasteBossSlamState::WasteBossSlamState(const std::string& name)
{
	m_name = name;
}
