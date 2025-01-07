#include "HitBoxManager.h"

#include "AABB.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "Collider.h"
#include "GameObject.h"
#include "GameplayConstants.h"
#include "Graphics.h"
#include "HitBoxData.h"
#include "Sprite.h"
#include "Spritesheet.h"

#include <directxtk/SimpleMath.h>
#include <vector>

using namespace GameplayConstants;

HitBoxManager::HitBoxManager() :
	m_owner(nullptr),
	m_sprite(nullptr),
	m_hitBoxDataList(0),
	m_isVisible(false)
{
}


HitBoxManager::~HitBoxManager()
{
	delete m_sprite;
	m_sprite = nullptr;

	m_hitBoxDataList.clear();
	m_pushBox.Delete();
	m_hitBox.Delete();
	m_hurtBox.Delete();
}

void HitBoxManager::Init(GameObject* owner, std::vector<HitBoxData> hitBoxData)
{
	m_sprite = new Sprite();
	m_sprite->Init(AssetLoader::GetTexture("t_pixel"));
	m_owner = owner;

	m_hitBoxDataList = hitBoxData;

	m_pushBox.Init(m_sprite, Colors::Blue.v);
	m_hurtBox.Init(m_sprite, Colors::Green.v);
	m_hitBox.Init(m_sprite, Colors::Red.v);
}

void HitBoxManager::Update()
{
	Vector2 ownerPosition = m_owner->GetPosition();
	m_pushBox.Update(ownerPosition);
	m_hurtBox.Update(ownerPosition);
	m_hitBox.Update(ownerPosition);
}

void HitBoxManager::Update(const unsigned int& frameNumber)
{
	UpdateCollider(frameNumber, m_pushBoxTagData, m_pushBox);
	UpdateCollider(frameNumber, m_hitBoxTagData, m_hitBox);
	UpdateCollider(frameNumber, m_hurtBoxTagData, m_hurtBox);

	Update();
}

void HitBoxManager::UpdateCollider(const unsigned int& frameNumber, TagData& tagData, Collider& collider)
{
	auto frame = FrameData::GetFrameData(frameNumber, tagData.frameData);
	Vector2 origin = m_owner->GetSprite()->GetOrigin();

	AABB aabb;
	aabb.SetMin(Vector2(frame.bounds.x - origin.x, frame.bounds.y - origin.y));
	aabb.SetMax(Vector2(aabb.GetMin().x + frame.bounds.width, aabb.GetMin().y + frame.bounds.height));

	collider.SetAABB(aabb);
}

void HitBoxManager::Render(Graphics* graphics, Camera* camera)
{
	if(!m_isVisible)
		return;

	Vector2 screenPosition = m_owner->GetPosition();

	if(camera != nullptr)
		screenPosition -= camera->GetPosition();

	m_pushBox.Render(graphics, screenPosition);
	m_hurtBox.Render(graphics, screenPosition);

	if(IsHitBoxActive())
	{
		m_hitBox.Render(graphics, screenPosition);
	}
}

void HitBoxManager::SetOwner(GameObject* owner)
{
	m_owner = owner;
}

void HitBoxManager::SetCollidersUsingTag(const std::string &name)
{
	HitBoxData pushBox;
	HitBoxData hitBox;
	HitBoxData hurtBox;

	pushBox = HitBoxData::GetHitboxData(PushBoxName, m_hitBoxDataList);
	hitBox = HitBoxData::GetHitboxData(HitBoxName, m_hitBoxDataList);
	hurtBox = HitBoxData::GetHitboxData(HurtBoxName, m_hitBoxDataList);

	m_pushBoxTagData = TagData::GetTagData(name, pushBox.tagData);
	m_hitBoxTagData = TagData::GetTagData(name, hitBox.tagData);
	m_hurtBoxTagData = TagData::GetTagData(name, hurtBox.tagData);

	Update(0);
}

void HitBoxManager::SetFlipped(bool flip)
{
	m_pushBox.SetFlipped(flip);
	m_hitBox.SetFlipped(flip);
	m_hurtBox.SetFlipped(flip);
}

bool HitBoxManager::IsHitBoxActive()
{
	return m_hitBox.GetAABB().GetMin().x != m_hitBox.GetAABB().GetMax().x &&
		m_hitBox.GetAABB().GetMin().y != m_hitBox.GetAABB().GetMax().y;
}