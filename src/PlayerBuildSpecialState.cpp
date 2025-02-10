#include "PlayerBuildSpecialState.h"

#include "Animator.h"
#include "Player.h"
#include "State.h"

#include <directxtk/SimpleMath.h>
#include <string>

PlayerBuildSpecialState* PlayerBuildSpecialState::Instance()
{
    static PlayerBuildSpecialState instance("buildSpecial");
    return &instance;
}

PlayerBuildSpecialState::PlayerBuildSpecialState(const std::string& name)
{
    m_name = name;
}

void PlayerBuildSpecialState::OnEnter(Player* player)
{
    player->GetAnimator()->Reset();
    player->GetAnimator()->SetAnimation(m_name);
    player->GetHitBoxManager()->SetCollidersUsingTag(m_name);
}

void PlayerBuildSpecialState::Execute(Player* player)
{
    player->SetVelocity(Vector2::Zero);
}

void PlayerBuildSpecialState::OnExit(Player* player)
{
}