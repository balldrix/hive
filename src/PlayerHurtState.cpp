#include "PlayerHurtState.h"

#include "Player.h"
#include "PlayerIdleState.h"

PlayerHurtState* PlayerHurtState::Instance()
{
	static PlayerHurtState instance("hurt");
	return &instance;
}

void PlayerHurtState::OnEnter(Player* player)
{
	player->Stop();
	player->GetAnimator()->Reset();
	player->GetAnimator()->SetAnimation(m_name);
	player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
	player->SetHurtTimer(0.0f);
}

void PlayerHurtState::Execute(Player* player)
{
	if (player->GetHurtTimer() > 0.5f)
	{
		player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}
}

void PlayerHurtState::OnExit(Player* player)
{
}

PlayerHurtState::PlayerHurtState(const std::string &name)
{
	m_name = name;
}
