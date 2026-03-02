#include "TriggerCollider.h"

#include "AssetLoader.h"
#include "Collider.h"
#include "Sprite.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>

TriggerCollider::TriggerCollider() :
	m_data(),
	m_triggerType(),
	Collider()
{
}

TriggerCollider::~TriggerCollider()
{
}

void TriggerCollider::Init(TriggerType type, TriggerColliderData data)
{
	Sprite* sprite = new Sprite();
	sprite->Init(AssetLoader::GetTexture("t_pixel"));
	Collider::Init(sprite, Colors::Aqua.v);
	m_triggerType = type;
	m_data = data;
}
